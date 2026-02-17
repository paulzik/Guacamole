#include "Gizmos.h"
#include <glm/geometric.hpp>
#include <glm/gtc/constants.hpp>

void Gizmos::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
	lines.push_back(GizmoLine(start, end, color));
}

void Gizmos::DrawArrow(const glm::vec3& start, const glm::vec3& direction, float length, const glm::vec3& color) {
	
}

void Gizmos::DrawCircle(
    const glm::vec3& center,
    const glm::vec3& normal,
    float radius,
    const glm::vec3& color)
{
    const int segments = 32;

    glm::vec3 n = glm::normalize(normal);

    glm::vec3 helper =
        (fabs(n.y) > 0.99f)
        ? glm::vec3(1, 0, 0)
        : glm::vec3(0, 1, 0);

    glm::vec3 tangent = glm::normalize(glm::cross(n, helper));
    glm::vec3 bitangent = glm::normalize(glm::cross(n, tangent));

    float step = glm::two_pi<float>() / segments;

    glm::vec3 prevPoint;

    for (int i = 0; i <= segments; i++)
    {
        float angle = i * step;

        glm::vec3 point =
            center +
            tangent * cos(angle) * radius +
            bitangent * sin(angle) * radius;

        if (i > 0)
            DrawLine(prevPoint, point, color);

        prevPoint = point;
    }
}

void Gizmos::DrawSphere(
    const glm::vec3& center,
    float radius,
    const glm::vec3& color)
{
    // XY plane
    DrawCircle(center, glm::vec3(0, 0, 1), radius, color);

    // XZ plane
    DrawCircle(center, glm::vec3(0, 1, 0), radius, color);

    // YZ plane
    DrawCircle(center, glm::vec3(1, 0, 0), radius, color);
}

void Gizmos::DrawBox(const glm::vec3& center, const glm::vec3& size, const glm::vec3& color) {
	//Base
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x/2), center.y - (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x - (size.x / 2), center.y - (size.y / 2), center.z + (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x + (size.x/2), center.y - (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y - (size.y / 2), center.z + (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x / 2), center.y - (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y - (size.y / 2), center.z - (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x / 2), center.y - (size.y / 2), center.z + (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y - (size.y / 2), center.z + (size.z / 2)), color));
	
	//Top
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x / 2), center.y + (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x - (size.x / 2), center.y + (size.y / 2), center.z + (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x + (size.x / 2), center.y + (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y + (size.y / 2), center.z + (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x / 2), center.y + (size.y / 2), center.z - (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y + (size.y / 2), center.z - (size.z / 2)), color));
	lines.push_back(GizmoLine(glm::vec3(center.x - (size.x / 2), center.y + (size.y / 2), center.z + (size.z / 2)), glm::vec3(center.x + (size.x / 2), center.y + (size.y / 2), center.z + (size.z / 2)), color));

	//Verticals
	lines.push_back(GizmoLine(glm::vec3(center.x - size.x / 2, center.y - size.y / 2, center.z - size.z / 2), glm::vec3(center.x - size.x / 2, center.y + size.y / 2, center.z - size.z / 2), color));
	lines.push_back(GizmoLine(glm::vec3(center.x + size.x / 2, center.y - size.y / 2, center.z - size.z / 2), glm::vec3(center.x + size.x / 2, center.y + size.y / 2, center.z - size.z / 2), color));
	lines.push_back(GizmoLine(glm::vec3(center.x - size.x / 2, center.y - size.y / 2, center.z + size.z / 2), glm::vec3(center.x - size.x / 2, center.y + size.y / 2, center.z + size.z / 2), color));
	lines.push_back(GizmoLine(glm::vec3(center.x + size.x / 2, center.y - size.y / 2, center.z + size.z / 2), glm::vec3(center.x + size.x / 2, center.y + size.y / 2, center.z + size.z / 2), color));
}

void Gizmos::DrawHemisphere(
    const glm::vec3& center,
    const glm::vec3& up,
    float radius,
    const glm::vec3& color)
{
    const int segments = 32;

    glm::vec3 n = glm::normalize(up);

    glm::vec3 helper =
        (fabs(n.y) > 0.99f)
        ? glm::vec3(1, 0, 0)
        : glm::vec3(0, 1, 0);

    glm::vec3 right = glm::normalize(glm::cross(n, helper));
    glm::vec3 forward = glm::normalize(glm::cross(right, n));

    float step = glm::pi<float>() / segments;

    // Draw vertical half-circles
    for (int axis = 0; axis < 2; axis++)
    {
        glm::vec3 axisDir = (axis == 0) ? right : forward;

        glm::vec3 prev;

        for (int i = 0; i <= segments; i++)
        {
            float angle = i * step;

            glm::vec3 point =
                center +
                axisDir * cos(angle) * radius +
                n * sin(angle) * radius;

            if (i > 0)
                DrawLine(prev, point, color);

            prev = point;
        }
    }
}


void Gizmos::DrawCapsule(
    const glm::vec3& center,
    float height,
    float radius,
    const glm::vec3& color)
{
    glm::vec3 up = glm::vec3(0, 1, 0);

    height = glm::max(height, radius * 2.0f);

    float cylinderHeight = height - (2.0f * radius);

    glm::vec3 topCenter =
        center + up * (cylinderHeight * 0.5f);

    glm::vec3 bottomCenter =
        center - up * (cylinderHeight * 0.5f);

    // Draw cylinder vertical lines
    glm::vec3 right = glm::vec3(radius, 0, 0);
    glm::vec3 forward = glm::vec3(0, 0, radius);

    DrawLine(topCenter + right, bottomCenter + right, color);
    DrawLine(topCenter - right, bottomCenter - right, color);
    DrawLine(topCenter + forward, bottomCenter + forward, color);
    DrawLine(topCenter - forward, bottomCenter - forward, color);

    // Draw top & bottom circles
    DrawCircle(topCenter, up, radius, color);
    DrawCircle(bottomCenter, up, radius, color);

    // Draw hemispheres
    DrawHemisphere(topCenter, up, radius, color);
    DrawHemisphere(bottomCenter, -up, radius, color);
}


const std::vector<GizmoLine>& Gizmos::GetLines() {
	return lines;
}

void Gizmos::Clear()
{
	lines.clear();
}