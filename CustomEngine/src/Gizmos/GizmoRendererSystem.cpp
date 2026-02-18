#include "GizmoRendererSystem.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <glm/vec3.hpp>
#include "Assets/Shader.h"
#include "Gizmos.h"
#include "ECS/Scene.h"
#include "GizmoDrawerRegistry.h"

bool GizmoRendererSystem::Init()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Allocate empty buffer initially (dynamic, because it changes every frame)
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);

    // Layout:
    // vec3 position
    // vec3 color
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        sizeof(float) * 6,
        (void*)0
    );

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        sizeof(float) * 6,
        (void*)(sizeof(float) * 3)
    );

    glBindVertexArray(0);

    gizmoShader = Shader::FromFiles("Assets/Shaders/GizmosVertex.vert", "Assets/Shaders/GizmosFragment.frag");

    return true;
}


void GizmoRendererSystem::Update()
{
    Gizmos::Clear();

    Entity* selectedEntity = Scene::Get().selectedEntity;
    if (!selectedEntity)
        return;

    auto& registry = GizmoDrawerRegistry::GetRegistry();
    for (auto& [type, drawer] : registry)
    {
        if (selectedEntity->HasComponent(type))
        {
            drawer->DrawGizmos(selectedEntity);
        }
    }

    const auto& lines = Gizmos::GetLines();

    if (lines.empty())
        return;

    std::vector<float> vertices;
    vertices.reserve(lines.size() * 2 * 6);
    for (const auto& line : lines)
    {
        // Start
        vertices.push_back(line.start.x);
        vertices.push_back(line.start.y);
        vertices.push_back(line.start.z);
        vertices.push_back(line.color.r);
        vertices.push_back(line.color.g);
        vertices.push_back(line.color.b);

        // End
        vertices.push_back(line.end.x);
        vertices.push_back(line.end.y);
        vertices.push_back(line.end.z);
        vertices.push_back(line.color.r);
        vertices.push_back(line.color.g);
        vertices.push_back(line.color.b);
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_DYNAMIC_DRAW);

    glUseProgram(gizmoShader->programID);

    // Set matrices
    glUniformMatrix4fv(
        glGetUniformLocation(gizmoShader->programID, "view"),
        1, GL_FALSE,
        glm::value_ptr(Scene::Get().GetCamera()->viewMatrix)
    );

    glUniformMatrix4fv(
        glGetUniformLocation(gizmoShader->programID, "projection"),
        1, GL_FALSE,
        glm::value_ptr(Scene::Get().GetCamera()->projectionMatrix)
    );
    glBindVertexArray(vao);

    glDrawArrays(GL_LINES, 0, lines.size() * 2);

    glBindVertexArray(0);

    Gizmos::Clear();
}


void GizmoRendererSystem::Shutdown()
{
	//delete gizmoShader;
}
