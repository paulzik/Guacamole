#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class CameraEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
