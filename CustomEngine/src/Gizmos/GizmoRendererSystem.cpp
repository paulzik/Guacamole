#include "GizmoRendererSystem.h"

bool GizmoRendererSystem::Init()
{
	return false;
}

void GizmoRendererSystem::Update()
{
}

void GizmoRendererSystem::Shutdown()
{
	delete gizmoShader;
}
