#pragma once
#include "ComponentEditor.h"
#include "Audio/AudioSource.h"
#include <imgui.h>

class AudioSourceEditor : public ComponentEditor {
public:
    void Draw(Component* component) override;
};
