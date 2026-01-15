#include "AudioSourceEditor.h"
#include "EditorMacro.h"
#include <glm/gtc/type_ptr.hpp>

void AudioSourceEditor::Draw(Component* component) {
    AudioSource* audioSource = static_cast<AudioSource*>(component);
    ImGui::LabelText("AudioClip", audioSource->GetAudioClip()->GetAudioName().c_str());

    ImGui::SeparatorText("Controlls");
    float volume = audioSource->GetVolume();
    if (ImGui::SliderFloat("Volume", &volume, 0.0f, 1.0f)) {
        audioSource->SetVolume(volume);
    }

    float pitch = audioSource->GetPitch();
    if (ImGui::SliderFloat("Pitch", &pitch, 0.5f, 4.0f)) {
        audioSource->SetPitch(pitch);
    }

    bool loop = audioSource->GetLoop();
    if (ImGui::Checkbox("Loop", &loop)) {
        audioSource->SetLoop(loop);
    }

    ImGui::SeparatorText("Live");
    if (ImGui::Button("Play Audio")) {
        audioSource->Play();
    }
}

CUSTOM_EDITOR(AudioSource, AudioSourceEditor);
