#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class LightEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
