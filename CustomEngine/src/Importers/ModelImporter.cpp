#include "ModelImporter.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <stdexcept>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

std::shared_ptr<Asset> ModelImporter::Load(const std::string& path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(
        path,
        aiProcess_Triangulate |
        aiProcess_GenNormals |
        aiProcess_CalcTangentSpace |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices
    );

    if (!scene || !scene->HasMeshes())
    {
        throw std::runtime_error(
            "Failed to load model: " + path + "\n" +
            importer.GetErrorString()
        );
    }

    // --- Meshes ---
    auto meshFilters = ProcessScene(scene);

    // --- Skeleton ---
    std::shared_ptr<Skeleton> skeleton = nullptr;
    if (scene->HasAnimations())
    {
        skeleton = BuildSkeleton(scene);
        ExtractBoneWeights(scene, meshFilters, skeleton);
    }

    // --- Animations ---
    std::vector<std::shared_ptr<Animation>> animations;
    if (scene->HasAnimations() && skeleton)
    {
        animations = LoadAnimations(scene, skeleton);
    }

    return std::make_shared<Model>(
        meshFilters,
        skeleton,
        animations
    );
}


std::vector<std::shared_ptr<MeshFilter>> ModelImporter::ProcessScene(const aiScene* scene)
{
    std::vector<std::shared_ptr<MeshFilter>> meshes;

    for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[i];
        meshes.push_back(ProcessMesh(mesh, scene));
    }

    return meshes;
}

std::shared_ptr<MeshFilter> ModelImporter::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    // Extract vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        // Positions
        vertex.position = {
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        };

        // Normals
        if (mesh->HasNormals())
        {
            vertex.normal = {
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            };
        }
        else
        {
            vertex.normal = { 0.0f, 1.0f, 0.0f };
        }

        // Colors (optional)
        if (mesh->HasVertexColors(0))
        {
            vertex.color = {
                mesh->mColors[0][i].r,
                mesh->mColors[0][i].g,
                mesh->mColors[0][i].b
            };
        }
        else
        {
            vertex.color = { 1.0f, 1.0f, 1.0f };
        }

        // UVs (optional)
        if (mesh->HasTextureCoords(0)) // first UV set
        {
            vertex.uv = {
                mesh->mTextureCoords[0][i].x,
                1.0f - mesh->mTextureCoords[0][i].y
            };
        }
        else
        {
            vertex.uv = { 0.0f, 0.0f }; // default UV if none present
        }

        vertices.push_back(vertex);
    }

    // Extract indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    return std::make_shared<MeshFilter>(vertices, indices);
}


std::shared_ptr<Skeleton> ModelImporter::BuildSkeleton(const aiScene* scene)
{
    auto skeleton = std::make_shared<Skeleton>();

    if (!scene->mRootNode)
        return skeleton;

    // Recursive lambda to traverse the node hierarchy
    std::function<void(aiNode*, int)> traverse;
    traverse = [&](aiNode* node, int parentIndex)
        {
            // Create a bone for this node
            glm::mat4 offset = glm::transpose(glm::make_mat4(&node->mTransformation.a1)); // Assimp → glm
            int boneIndex = skeleton->AddBone(node->mName.C_Str(), parentIndex, offset);

            // Recurse for children
            for (unsigned int i = 0; i < node->mNumChildren; ++i)
            {
                traverse(node->mChildren[i], boneIndex);
            }
        };

    traverse(scene->mRootNode, -1);

    return skeleton;
}

void ModelImporter::ExtractBoneWeights(
    const aiScene* scene,
    std::vector<std::shared_ptr<MeshFilter>>& meshes,
    std::shared_ptr<Skeleton> skeleton)
{
    for (size_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex)
    {
        aiMesh* ai_mesh = scene->mMeshes[meshIndex];
        auto& meshFilter = meshes[meshIndex];
        auto& vertices = meshFilter->GetVerticesRef(); // non-const getter

        // Initialize bone info
        for (unsigned int b = 0; b < ai_mesh->mNumBones; ++b)
        {
            aiBone* ai_bone = ai_mesh->mBones[b];
            int boneIndex = skeleton->GetBoneIndex(ai_bone->mName.C_Str());
            if (boneIndex == -1)
            {
                // Bone not in skeleton, add it
                glm::mat4 offset = glm::transpose(glm::make_mat4(&ai_bone->mOffsetMatrix.a1));
                boneIndex = skeleton->AddBone(ai_bone->mName.C_Str(), -1, offset);
            }

            // Assign weights to vertices
            for (unsigned int w = 0; w < ai_bone->mNumWeights; ++w)
            {
                const aiVertexWeight& vw = ai_bone->mWeights[w];
                Vertex& vertex = vertices[vw.mVertexId];

                // find first empty slot
                for (int i = 0; i < 4; ++i)
                {
                    if (vertex.boneWeights[i] == 0.0f)
                    {
                        vertex.boneIDs[i] = boneIndex;
                        vertex.boneWeights[i] = vw.mWeight;
                        break;
                    }
                }
            }
        }

        // Optional: normalize weights
        for (Vertex& v : vertices)
        {
            float total = v.boneWeights[0] + v.boneWeights[1] + v.boneWeights[2] + v.boneWeights[3];
            if (total > 0)
            {
                v.boneWeights[0] /= total;
                v.boneWeights[1] /= total;
                v.boneWeights[2] /= total;
                v.boneWeights[3] /= total;
            }
        }
    }
}

std::vector<std::shared_ptr<Animation>> ModelImporter::LoadAnimations(
    const aiScene* scene,
    std::shared_ptr<Skeleton> skeleton)
{
    std::vector<std::shared_ptr<Animation>> animations;

    for (unsigned int i = 0; i < scene->mNumAnimations; ++i)
    {
        aiAnimation* aiAnim = scene->mAnimations[i];

        std::string animName = aiAnim->mName.C_Str();
        double duration = aiAnim->mDuration;
        double ticksPerSecond = aiAnim->mTicksPerSecond != 0.0 ? aiAnim->mTicksPerSecond : 25.0;

        auto animation = std::make_shared<Animation>(animName, duration);

        // Iterate channels (each channel corresponds to a bone)
        for (unsigned int c = 0; c < aiAnim->mNumChannels; ++c)
        {
            aiNodeAnim* channel = aiAnim->mChannels[c];
            int boneIndex = skeleton->GetBoneIndex(channel->mNodeName.C_Str());
            if (boneIndex == -1)
            {
                // Bone not in skeleton, skip
                continue;
            }

            // Store position keyframes
            for (unsigned int k = 0; k < channel->mNumPositionKeys; ++k)
            {
                const aiVectorKey& key = channel->mPositionKeys[k];
                animation->AddPositionKey(boneIndex, (float)key.mTime, glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
            }

            // Store rotation keyframes
            for (unsigned int k = 0; k < channel->mNumRotationKeys; ++k)
            {
                const aiQuatKey& key = channel->mRotationKeys[k];
                animation->AddRotationKey(boneIndex, (float)key.mTime, glm::quat(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z));
            }

            // Store scale keyframes
            for (unsigned int k = 0; k < channel->mNumScalingKeys; ++k)
            {
                const aiVectorKey& key = channel->mScalingKeys[k];
                animation->AddScaleKey(boneIndex, (float)key.mTime, glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
            }
        }

        animations.push_back(animation);
    }

    return animations;
}

