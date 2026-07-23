#include "AnimatorEditor.h"
#include "EditorMacro.h"
#include <imgui.h>

void AnimatorEditor::Draw(Component* component)
{
    Animator* animator = static_cast<Animator*>(component);
    if (!animator) return;

    // Unique ID for this Animator instance
    std::string uniqueID = std::to_string(reinterpret_cast<uintptr_t>(animator));

    if (!ImGui::TreeNode(("Animations##" + uniqueID).c_str()))
        return;

    const auto& animations = animator->animations;

    if (animations.empty())
    {
        ImGui::TextDisabled("No animations found");
        ImGui::TreePop();
        return;
    }

    // ---------- Animation Combo ----------
    int currentIndex = animator->currentAnimationIndex;
    const char* preview =
        (currentIndex >= 0 && currentIndex < animations.size())
        ? animations[currentIndex]->GetAnimationName().c_str()
        : "None";

    // Begin combo for selecting animation
    if (ImGui::BeginCombo(("Animation##" + uniqueID).c_str(), preview))
    {
        for (int i = 0; i < animations.size(); ++i)
        {
            bool selected = (i == currentIndex);
            if (ImGui::Selectable(animations[i]->GetAnimationName().c_str(), selected))
            {
                animator->PlayByIndex(i);
            }
            if (selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }

    ImGui::Spacing();
    ImGui::SeparatorText("Playback");

    // ---------- Time Slider ----------
    float time = animator->currentAnimationTime;
    float duration = animator->currentAnimation->GetDuration();

    if (duration > 0.0f)
    {
        if (ImGui::SliderFloat(("Time##" + uniqueID).c_str(), &time, 0.0f, duration))
        {
            animator->currentAnimationTime = time;
        }
    }

    // ---------- Loop Checkbox (outside combo) ----------
    bool loop = animator->loop;
    if (ImGui::Checkbox(("Loop##" + uniqueID).c_str(), &loop))
    {
        animator->loop = loop;
    }

    
    bool play = animator->play;
    if (ImGui::Checkbox(("Play##" + uniqueID).c_str(), &play))
    {
        animator->play = play;
    }
    
    ImGui::TreePop();

}

CUSTOM_EDITOR(Animator, AnimatorEditor);
