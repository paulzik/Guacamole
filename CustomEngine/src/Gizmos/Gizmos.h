#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "GizmoLine.h"

class Gizmos
{
public:
    static void DrawLine(
        const glm::vec3& start,
        const glm::vec3& end,
        const glm::vec3& color);

    static void DrawArrow(
        const glm::vec3& start,
        const glm::vec3& direction,
        float length,
        const glm::vec3& color);

    static void DrawBox(
        const glm::vec3& center,
        const glm::vec3& size,
        const glm::vec3& color);

    static const std::vector<GizmoLine>& GetLines();
    static void Clear();

private:
    static std::vector<GizmoLine> lines;
};
