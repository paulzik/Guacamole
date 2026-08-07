#pragma once
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 uv;

    int boneIDs[4] = { 0 };
    float boneWeights[4] = { 0 };
};