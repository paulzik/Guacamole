#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class DirectionalLightEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
