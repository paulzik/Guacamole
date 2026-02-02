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

bool RenderSystem::Init()
{
    /*
    if (material == nullptr) {

        std::cerr << "MeshRenderer ERROR: No material assigned! in entity: " << owner->GetName() << std::endl;
        return;
    }

    if (material->shader == nullptr) {
        std::cerr << "MeshRenderer ERROR: No shader assigned! in entity: " << owner->GetName() << std::endl;
        return;
    }
    */
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
}

void RenderSystem::Shutdown()
{
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

