#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class MeshRendererEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
