#include "MenuBar.h"
#include <imgui.h>
#include <SDL3/SDL.h>

MenuBar::MenuBar(std::vector<std::unique_ptr<EditorWindow>>* windows)
    : EditorWindow("MenuBar"), windows(windows) {
}

void MenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New Scene")) {}
            if (ImGui::MenuItem("Open Scene")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Save ")) {}
            if (ImGui::MenuItem("Save As")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Exit")) {
                SDL_Event quit{ SDL_EVENT_QUIT };
                SDL_PushEvent(&quit);
            }
            ImGui::EndMenu();
        }

        ImGui::Separator();
        if (ImGui::BeginMenu("Windows"))
        {
            for (auto& w : *windows)
                ImGui::MenuItem(w->GetName(), nullptr, &w->open);
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}