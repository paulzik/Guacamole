#pragma once
#include "ComponentEditor.h"
#include "ECS/Transform.h"
#include <imgui.h>

class TransformEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
