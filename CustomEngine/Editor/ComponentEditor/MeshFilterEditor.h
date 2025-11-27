#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class MeshFilterEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
