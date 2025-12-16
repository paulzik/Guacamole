#pragma once
#include "ComponentEditor.h"
#include "Animations/Animator.h"
#include <imgui.h>

class AnimatorEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
