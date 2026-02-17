#include "Gizmos.h"

void Gizmos::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
	lines.push_back(GizmoLine(start, end, color));
}


void Gizmos::DrawArrow(const glm::vec3& start, const glm::vec3& direction, float length, const glm::vec3& color) {

}

void Gizmos::DrawBox(const glm::vec3& center, const glm::vec3& size, const glm::vec3& color) {

}

const std::vector<GizmoLine>& Gizmos::GetLines() {
	return lines;
}

void Gizmos::Clear()
{
	lines.clear();
}