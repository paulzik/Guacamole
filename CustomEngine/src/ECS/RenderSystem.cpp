#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec3.hpp>
#include "RenderSystem.h"
#include "SkinnedMeshRenderer.h"
#include "ECS/Transform.h"
#include "Lighting/Light.h"
#include "ECS/Entity.h"
#include "Scene.h"
#include "ECS/MeshFilter.h"
#include <Lighting/DirectionalLight.h>
#include <Lighting/PointLight.h>
#include "TransformUtils.h"
#include <Animations/Animator.h>

bool RenderSystem::Init()
{
    return true;
}

void RenderSystem::TryRegister(Component* c)
{
    if (auto mr = dynamic_cast<MeshRenderer*>(c))
        meshRenderers.push_back(mr);

    if (auto smr = dynamic_cast<SkinnedMeshRenderer*>(c))
        skinnedRenderers.push_back(smr);
}

void RenderSystem::Update()
{
    for (auto renderer : meshRenderers) {
        UpdateMeshRenderers(renderer);
    }

    for (auto renderer : skinnedRenderers) {
        UpdateSkinnedMeshRenderers(renderer);
    }
}

void RenderSystem::Shutdown()
{
    meshRenderers.clear();
    skinnedRenderers.clear();
}


void RenderSystem::UpdateMeshRenderers(MeshRenderer* meshRenderer)
{
    if (!meshRenderer->material) {
        std::cerr << "MeshRenderer ERROR: No material assigned! in entity: " << meshRenderer->owner->GetName() << std::endl;
        return;
    }
    if (meshRenderer->material->shader->programID == 0) {
        std::cerr << "MeshRenderer ERROR: Shader program not compiled!\n";
        return;
    }

    Transform& transform = meshRenderer->owner->GetComponent<Transform>();

    glUseProgram(meshRenderer->material->shader->programID);

    // -----------------------------
    // SET UNIFORMS
    // -----------------------------
    glUniformMatrix4fv(
        glGetUniformLocation(meshRenderer->material->shader->programID, "model"),
        1, GL_FALSE, glm::value_ptr(transform.modelMatrix)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(meshRenderer->material->shader->programID, "view"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->viewMatrix)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(meshRenderer->material->shader->programID, "projection"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->projectionMatrix)
    );

    // -----------------------------
    // Camera
    // -----------------------------
    glUniform3fv(
        glGetUniformLocation(meshRenderer->material->shader->programID, "viewPos"),
        1, glm::value_ptr(Scene::Get().GetCamera()->owner->GetComponent<Transform>().position)
    );

    // -----------------------------
    // Lights
    // -----------------------------
    const auto& lights = Scene::Get().GetLights();
    int lightCount = static_cast<int>(lights.size());

    glUniform1i(glGetUniformLocation(meshRenderer->material->shader->programID, "lightCount"), lightCount);

    for (int i = 0; i < lightCount; i++)
    {
        Light* light = lights[i];
        Transform& tr = light->owner->GetComponent<Transform>();

        std::string base = "lights[" + std::to_string(i) + "]";

        glUniform1i(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".type").c_str()), light->GetType());
        glUniform3fv(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".color").c_str()), 1, glm::value_ptr(light->GetColor()));
        glUniform1f(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".intensity").c_str()), light->GetIntensity());

        if (light->GetType() == LightType::POINT)
        {
            auto* pointLight = static_cast<PointLight*>(light);
            glm::vec3 pos = tr.position;
            glUniform3fv(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".position").c_str()), 1, glm::value_ptr(pos));
            glUniform1f(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".radius").c_str()), pointLight->GetRadius());

        }
        else if (light->GetType() == LightType::DIRECTIONAL)
        {
            auto* directionalLight = static_cast<DirectionalLight*>(light);
            glm::vec3 dir = GetForward(tr);
            glUniform3fv(glGetUniformLocation(meshRenderer->material->shader->programID, (base + ".direction").c_str()), 1, glm::value_ptr(dir));
        }
    }

    glUniform1i(glGetUniformLocation(meshRenderer->material->shader->programID, "useTexture"), meshRenderer->material->albedo != nullptr);

    if (meshRenderer->material->albedo) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, meshRenderer->material->albedo->ID); // Bind your texture
        glUniform1i(glGetUniformLocation(meshRenderer->material->shader->programID, "albedoTexture"), 0); // Texture unit 0    
    }

    glUniform1f(glGetUniformLocation(meshRenderer->material->shader->programID, "metallic"), meshRenderer->material->metallic);

    // -----------------------------
    // DRAW MESH
    // -----------------------------
    MeshFilter& mesh = meshRenderer->owner->GetComponent<MeshFilter>();

    glBindVertexArray(mesh.VAO);
    if (meshRenderer->wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}

void RenderSystem::UpdateSkinnedMeshRenderers(SkinnedMeshRenderer* skinnedMeshRenderer)
{
    if (!skinnedMeshRenderer->material) {
        std::cerr << "SkinnedMeshRenderer ERROR: No material assigned!\n";
        return;
    }
    if (skinnedMeshRenderer->material->shader->programID == 0) {
        std::cerr << "SkinnedMeshRenderer ERROR: Shader program not compiled!\n";
        return;
    }

    Transform& transform = skinnedMeshRenderer->owner->GetComponent<Transform>();

    glUseProgram(skinnedMeshRenderer->material->shader->programID);

    // -----------------------------
    // SET UNIFORMS
    // -----------------------------
    glUniformMatrix4fv(
        glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "model"),
        1, GL_FALSE, glm::value_ptr(transform.modelMatrix)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "view"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->viewMatrix)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "projection"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->projectionMatrix)
    );

    // -----------------------------
    // Camera
    // -----------------------------
    glUniform3fv(
        glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "viewPos"),
        1, glm::value_ptr(Scene::Get().GetCamera()->owner->GetComponent<Transform>().position)
    );

    // -----------------------------
    // Lights
    // -----------------------------
    const auto& lights = Scene::Get().GetLights();
    int lightCount = static_cast<int>(lights.size());

    glUniform1i(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "lightCount"), lightCount);

    for (int i = 0; i < lightCount; i++)
    {
        Light* light = lights[i];
        Transform& tr = light->owner->GetComponent<Transform>();

        std::string base = "lights[" + std::to_string(i) + "]";

        glUniform1i(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".type").c_str()), light->GetType());
        glUniform3fv(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".color").c_str()), 1, glm::value_ptr(light->GetColor()));
        glUniform1f(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".intensity").c_str()), light->GetIntensity());

        if (light->GetType() == LightType::POINT)
        {
            auto* pointLight = static_cast<PointLight*>(light);
            glm::vec3 pos = tr.position;
            glUniform3fv(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".position").c_str()), 1, glm::value_ptr(pos));
            glUniform1f(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".radius").c_str()), pointLight->GetRadius());

        }
        else if (light->GetType() == LightType::DIRECTIONAL)
        {
            auto* directionalLight = static_cast<DirectionalLight*>(light);
            glm::vec3 dir = GetForward(tr);
            glUniform3fv(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, (base + ".direction").c_str()), 1, glm::value_ptr(dir));
        }
    }

    glUniform1i(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "useTexture"), skinnedMeshRenderer->material->albedo != nullptr);

    if (skinnedMeshRenderer->material->albedo) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, skinnedMeshRenderer->material->albedo->ID); // Bind your texture
        glUniform1i(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "albedoTexture"), 0); // Texture unit 0    
    }

    glUniform1f(glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, "metallic"), skinnedMeshRenderer->material->metallic);

    Animator& animator = skinnedMeshRenderer->owner->GetComponent<Animator>();
    if (&animator && animator.GetModel() && animator.GetModel()->skeleton)
    {
        Skeleton* skeleton = animator.GetModel()->skeleton.get();
        const int boneCount = skeleton->GetBoneCount();

        for (int i = 0; i < boneCount; ++i)
        {
            std::string uniformName = "bones[" + std::to_string(i) + "]";

            // FIX: Multiply Global Transform by the Offset Matrix (Inverse Bind Pose)
            const Bone& bone = skeleton->GetBone(i);
            glm::mat4 finalTransform = bone.globalTransform * bone.offsetMatrix;

            glUniformMatrix4fv(
                glGetUniformLocation(skinnedMeshRenderer->material->shader->programID, uniformName.c_str()),
                1, GL_FALSE, glm::value_ptr(finalTransform)
            );
        }
    }

    // -----------------------------
    // DRAW MESH
    // -----------------------------
    MeshFilter& mesh = skinnedMeshRenderer->owner->GetComponent<MeshFilter>();

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.indices.size(), GL_UNSIGNED_INT, 0);
}

