#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class PointLightEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
