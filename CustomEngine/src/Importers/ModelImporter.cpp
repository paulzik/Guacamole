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
// NEW
            glm::mat4 localBindPose = AssimpToGLM(node->mTransformation);
            int boneIndex = skeleton->AddBone(node->mName.C_Str(), parentIndex, localBindPose);

            // Recurse for children
            for (unsigned int i = 0; i < node->mNumChildren; ++i)
            {
                traverse(node->mChildren[i], boneIndex);
            }
        };
    traverse(scene->mRootNode, -1);

    return skeleton;
}

glm::mat4 ModelImporter::AssimpToGLM(const aiMatrix4x4& from) {
    glm::mat4 to;
    // [col][row]
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
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
        auto& vertices = meshFilter->GetVerticesRef();

        for (unsigned int b = 0; b < ai_mesh->mNumBones; ++b)
        {
            aiBone* ai_bone = ai_mesh->mBones[b];
            int boneIndex = skeleton->GetBoneIndex(ai_bone->mName.C_Str());

            // 1. Correctly convert the Offset Matrix
            glm::mat4 offsetMatrix = AssimpToGLM(ai_bone->mOffsetMatrix);

            if (boneIndex == -1) {
                // Should rarely happen if BuildSkeleton worked correctly
                boneIndex = skeleton->AddBone(ai_bone->mName.C_Str(), -1, glm::mat4(1.0f));
            }

            // 2. STORE THE OFFSET MATRIX IN THE SKELETON
            skeleton->SetBoneOffset(boneIndex, offsetMatrix);

            // 3. Assign weights to vertices
            for (unsigned int w = 0; w < ai_bone->mNumWeights; ++w) {
                const aiVertexWeight& vw = ai_bone->mWeights[w];
                Vertex& vertex = vertices[vw.mVertexId];

                for (int i = 0; i < 4; ++i) {
                    if (vertex.boneWeights[i] == 0.0f) {
                        vertex.boneIDs[i] = boneIndex;
                        vertex.boneWeights[i] = vw.mWeight;
                        break;
                    }
                }
            }
        }
        // ... (Optional: Normalize weights)
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

        // Determine ticks per second
        double ticksPerSecond = aiAnim->mTicksPerSecond != 0.0
            ? aiAnim->mTicksPerSecond
            : 25.0;

        // Convert animation duration from ticks to seconds
        float durationSeconds = static_cast<float>(aiAnim->mDuration / ticksPerSecond);

        // Create animation asset
        auto animation = std::make_shared<Animation>(animName, durationSeconds);

        // Iterate channels (each channel corresponds to a bone)
        for (unsigned int c = 0; c < aiAnim->mNumChannels; ++c)
        {
            aiNodeAnim* channel = aiAnim->mChannels[c];
            int boneIndex = skeleton->GetBoneIndex(channel->mNodeName.C_Str());
            if (boneIndex == -1)
                continue; // Skip bones not in the skeleton

            // Store position keyframes (convert times to seconds)
            for (unsigned int k = 0; k < channel->mNumPositionKeys; ++k)
            {
                const aiVectorKey& key = channel->mPositionKeys[k];
                float timeSeconds = static_cast<float>(key.mTime / ticksPerSecond);
                animation->AddPositionKey(boneIndex, timeSeconds,
                    glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
            }

            // Store rotation keyframes (convert times to seconds)
            for (unsigned int k = 0; k < channel->mNumRotationKeys; ++k)
            {
                const aiQuatKey& key = channel->mRotationKeys[k];
                float timeSeconds = static_cast<float>(key.mTime / ticksPerSecond);
                animation->AddRotationKey(boneIndex, timeSeconds,
                    glm::quat(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z));
            }

            // Store scale keyframes (convert times to seconds)
            for (unsigned int k = 0; k < channel->mNumScalingKeys; ++k)
            {
                const aiVectorKey& key = channel->mScalingKeys[k];
                float timeSeconds = static_cast<float>(key.mTime / ticksPerSecond);
                animation->AddScaleKey(boneIndex, timeSeconds,
                    glm::vec3(key.mValue.x, key.mValue.y, key.mValue.z));
            }
        }

        animations.push_back(animation);
    }

    return animations;
}
