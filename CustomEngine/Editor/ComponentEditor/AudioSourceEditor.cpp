#include "AudioSourceEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void AudioSourceEditor::Draw(Component* component) {
    AudioSource* audioSource = static_cast<AudioSource*>(component);
    ImGui::LabelText("AudioClip", audioSource->clip->GetAudioName().c_str());

    ImGui::SeparatorText("Controlls");
    float volume = audioSource->volume;
    if (ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f)) {
        audioSource->volume = volume;
    }

    float pitch = audioSource->pitch;
    if (ImGui::SliderFloat("Pitch", &pitch, 0.5f, 4.0f)) {
        audioSource->pitch = pitch;
    }

    bool loop = audioSource->loop;
    if (ImGui::Checkbox("Loop", &loop)) {
        audioSource->loop = loop;
    }

    ImGui::SeparatorText("Live");
    if (ImGui::Button("Play Audio")) {
        audioSource->Play();
    }
}

CUSTOM_EDITOR(AudioSource, AudioSourceEditor);
