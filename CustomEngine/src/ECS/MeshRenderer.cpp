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

void MeshRenderer::Update()
{
    if (!material) {
        std::cerr << "MeshRenderer ERROR: No material assigned!\n";
        return;
    }
    if (material->shader->programID == 0) {
        std::cerr << "MeshRenderer ERROR: Shader program not compiled!\n";
        return;
    }

    Transform& transform = owner->GetComponent<Transform>();

    glUseProgram(material->shader->programID);

    // -----------------------------
    // SET UNIFORMS
    // -----------------------------
    glUniformMatrix4fv(
        glGetUniformLocation(material->shader->programID, "model"),
        1, GL_FALSE, glm::value_ptr(transform.GetModelMatrix())
    );

    glUniformMatrix4fv(
        glGetUniformLocation(material->shader->programID, "view"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->GetViewMatrix())
    );

    glUniformMatrix4fv(
        glGetUniformLocation(material->shader->programID, "projection"),
        1, GL_FALSE, glm::value_ptr(Scene::Get().GetCamera()->GetProjectionMatrix())
    );

    // -----------------------------
    // Camera
    // -----------------------------
    glUniform3fv(
        glGetUniformLocation(material->shader->programID, "viewPos"),
        1, glm::value_ptr(Scene::Get().GetCamera()->getOwner()->GetComponent<Transform>().GetPosition())
    );

    // -----------------------------
    // Lights
    // -----------------------------
    const auto& lights = Scene::Get().GetLights();
    int lightCount = static_cast<int>(lights.size());

    glUniform1i(glGetUniformLocation(material->shader->programID, "lightCount"), lightCount);

    for (int i = 0; i < lightCount; i++)
    {
        Light* light = lights[i];
        Transform& tr = light->getOwner()->GetComponent<Transform>();

        std::string base = "lights[" + std::to_string(i) + "]";

        glUniform1i(glGetUniformLocation(material->shader->programID, (base + ".type").c_str()), light->GetType());
        glUniform3fv(glGetUniformLocation(material->shader->programID, (base + ".color").c_str()), 1, glm::value_ptr(light->GetColor()));
        glUniform1f(glGetUniformLocation(material->shader->programID, (base + ".intensity").c_str()), light->GetIntensity());

        if (light->GetType() == LightType::POINT)
        {
            auto* pointLight = static_cast<PointLight*>(light);
            glm::vec3 pos = tr.GetPosition();
            glUniform3fv(glGetUniformLocation(material->shader->programID, (base + ".position").c_str()), 1, glm::value_ptr(pos));
            glUniform1f(glGetUniformLocation(material->shader->programID, (base + ".radius").c_str()), pointLight->GetRadius());

        }
        else if (light->GetType() == LightType::DIRECTIONAL)
        {
            auto* directionalLight = static_cast<DirectionalLight*>(light);
            glm::vec3 dir = tr.GetForward();
            glUniform3fv(glGetUniformLocation(material->shader->programID, (base + ".direction").c_str()), 1, glm::value_ptr(dir));
        }
    }

    glUniform1i(glGetUniformLocation(material->shader->programID, "useTexture"), material->albedo != nullptr);

    if (material->albedo) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->albedo->ID); // Bind your texture
        glUniform1i(glGetUniformLocation(material->shader->programID, "albedoTexture"), 0); // Texture unit 0    
    }

    glUniform1f(glGetUniformLocation(material->shader->programID, "metallic"), material->metallic);

    // -----------------------------
    // DRAW MESH
    // -----------------------------
    MeshFilter& mesh = owner->GetComponent<MeshFilter>();

    glBindVertexArray(mesh.VAO);
    glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
}

const char* MeshRenderer::GetComponentName() const  {
	return "MeshRenderer";
}