#pragma once
#include "ComponentEditor/ComponentEditor.h"
#include "Physics/RigidBody.h"


class RigidBodyEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
