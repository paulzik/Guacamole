#pragma once
#include "Gizmos/IGizmoDrawer.h"

class SphereColliderGizmoDrawer : public IGizmoDrawer
{
public:
    void DrawGizmos(Entity* entity) override;
};
