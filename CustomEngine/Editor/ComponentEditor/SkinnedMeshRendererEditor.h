#pragma once
#include "ComponentEditor.h"
#include <imgui.h>

class SkinnedMeshRendererEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
