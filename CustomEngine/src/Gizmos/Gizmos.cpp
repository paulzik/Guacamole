#include "Gizmos.h"

void Gizmos::DrawLine(const glm::vec3& start, const glm::vec3& end, const glm::vec3& color) {
	lines.push_back(GizmoLine(start, end, color));
}


void Gizmos::DrawArrow(const glm::vec3& start, const glm::vec3& direction, float length, const glm::vec3& color) {
	
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

const std::vector<GizmoLine>& Gizmos::GetLines() {
	return lines;
}

void Gizmos::Clear()
{
	lines.clear();
}