#include "AudioSourceEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void AudioSourceEditor::Draw(Component* component) {
    AudioSource* audioSource = static_cast<AudioSource*>(component);

    //glm::vec3 pos = audioSource->GetPosition();
    //if (ImGui::DragFloat3("Position", glm::value_ptr(pos), 0.1f, 0.0f, 0.0f)) {
   //     audioSource->SetPosition(pos);
   // }

}

CUSTOM_EDITOR(AudioSource, AudioSourceEditor);
