#pragma once
#include <glm/vec3.hpp>
#include <vector>
#include "GizmoLine.h"

class Gizmos
{
public:
    static void DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
    static void DrawAxes(const glm::vec3& start);
    static void DrawArrow(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color);
    static void DrawCone(const glm::vec3& tip, const glm::vec3& direction, float height, float radius, const glm::vec3& color, int segments);
    static void DrawBox(const glm::vec3& center, const glm::vec3& size, const glm::vec3& color);
    static void DrawCircle(const glm::vec3& center, const glm::vec3& normal, float radius, const glm::vec3& color);
    static void DrawSphere(const glm::vec3& center, float radius, const glm::vec3& color);
    static void DrawCapsule(const glm::vec3& center, float height, float radius, const glm::vec3& color);
    static void DrawHemisphere(const glm::vec3& center,  const glm::vec3& up, float radius, const glm::vec3& color);

    static const std::vector<GizmoLine>& GetLines();
    static void Clear();

private:
    static inline std::vector<GizmoLine> lines;
};
