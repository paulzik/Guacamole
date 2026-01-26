#pragma once
#include "ComponentEditor/ComponentEditor.h"
#include "Physics/Collider.h"


class ColliderEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
