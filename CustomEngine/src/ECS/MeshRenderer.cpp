#include "MeshRenderer.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "glm/mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ECS/MeshFilter.h"
#include "ECS/Entity.h"
#include "ECS/Transform.h"
#include "ECS/Scene.h"
#include <Lighting/PointLight.h>
#include <Lighting/DirectionalLight.h>
#include <Animations/Animator.h>

MeshRenderer::MeshRenderer()
{
}


MeshRenderer::~MeshRenderer() {

}

void MeshRenderer::Start()
{
    if (material == nullptr) {

        std::cerr << "MeshRenderer ERROR: No material assigned! in entity: " << owner->GetName() << std::endl;
        return;
    }

    if (material->shader == nullptr) {
        std::cerr << "MeshRenderer ERROR: No shader assigned! in entity: " << owner->GetName() << std::endl;
        return;
    }
}

void MeshRenderer::Draw(Shader* overrideShader, unsigned int entityID)
{
    if (!owner) return;

    Shader* shaderToUse = overrideShader ? overrideShader : material->shader.get();
    shaderToUse->Bind();

    Transform& transform = owner->GetComponent<Transform>();

    // -----------------------------
    // MODEL MATRIX
    // -----------------------------
    shaderToUse->SetMat4("model", transform.GetModelMatrix());

    // -----------------------------
    // ENTITY ID (for picking)
    // -----------------------------
    if (overrideShader) {
        shaderToUse->SetUInt("u_EntityID", entityID);
    }
    else {
        // Normal rendering uniforms
        shaderToUse->SetMat4("view", Scene::Get().GetCamera()->GetViewMatrix());
        shaderToUse->SetMat4("projection", Scene::Get().GetCamera()->GetProjectionMatrix());
        shaderToUse->SetVec3("viewPos", Scene::Get().GetCamera()->getOwner()->GetComponent<Transform>().GetPosition());

        // Lights
        const auto& lights = Scene::Get().GetLights();
        shaderToUse->SetInt("lightCount", static_cast<int>(lights.size()));
        for (int i = 0; i < lights.size(); i++) {
            Light* light = lights[i];
            Transform& tr = light->getOwner()->GetComponent<Transform>();
            std::string base = "lights[" + std::to_string(i) + "]";
            shaderToUse->SetInt(base + ".type", light->GetType());
            shaderToUse->SetVec3(base + ".color", light->GetColor());
            shaderToUse->SetFloat(base + ".intensity", light->GetIntensity());

            if (light->GetType() == LightType::POINT) {
                PointLight* pl = static_cast<PointLight*>(light);
                shaderToUse->SetVec3(base + ".position", tr.GetPosition());
                shaderToUse->SetFloat(base + ".radius", pl->GetRadius());
            }
            else if (light->GetType() == LightType::DIRECTIONAL) {
                DirectionalLight* dl = static_cast<DirectionalLight*>(light);
                shaderToUse->SetVec3(base + ".direction", tr.GetForward());
            }
        }

        // Material / textures
        shaderToUse->SetInt("useTexture", material->albedo != nullptr);
        if (material->albedo) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, material->albedo->ID);
            shaderToUse->SetInt("albedoTexture", 0);
        }
        shaderToUse->SetFloat("metallic", material->metallic);
    }

    // -----------------------------
    // DRAW MESH
    // -----------------------------
    MeshFilter& mesh = owner->GetComponent<MeshFilter>();
    glBindVertexArray(mesh.GetVAO());
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}


void MeshRenderer::Update()
{
    Draw();
}

const char* MeshRenderer::GetComponentName() const  {
	return "MeshRenderer";
}