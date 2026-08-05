#include "MenuBar.h"
#include "Scene/SceneSerializer.h"
#include "Project/ProjectSettings.h"
#include "Importers/Resources.h"
#include <imgui.h>
#include <SDL3/SDL.h>
#include <filesystem>

static Uint32 s_openProjectEvent = 0;

MenuBar::MenuBar(std::vector<std::unique_ptr<EditorWindow>>* windows, SDL_Window* sdlWindow)
    : EditorWindow("MenuBar"), windows(windows), sdlWindow(sdlWindow)
{
    if (s_openProjectEvent == 0)
        s_openProjectEvent = SDL_RegisterEvents(1);
}

// May run on a background thread: it must only touch SDL's event queue.
static void OnFolderChosen(void* /*userdata*/, const char* const* filelist, int)
{
    // SDL distinguishes three outcomes: null list = error, empty list = cancelled.
    if (!filelist || !filelist[0])
        return;

    SDL_Event event{};
    event.type = s_openProjectEvent;
    event.user.data1 = SDL_strdup(filelist[0]);
    SDL_PushEvent(&event);
}

bool MenuBar::HandleEvent(const SDL_Event& event)
{
    if (s_openProjectEvent == 0 || event.type != s_openProjectEvent)
        return false;

    char* chosen = static_cast<char*>(event.user.data1);
    if (!chosen)
        return true;

    const std::filesystem::path folder = chosen;
    SDL_free(chosen);

    if (!ProjectSettings::Get().Load(folder / "project.yaml"))
        ProjectSettings::Get().UseFolder(folder);

    Resources::SetBasePath(ProjectSettings::Get().GetRootPath());

    return true;
}

void MenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Project")) {
                const std::string start = ProjectSettings::Get().GetRootPath().parent_path().string();
                SDL_ShowOpenFolderDialog(OnFolderChosen, this, sdlWindow, start.c_str(), false);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("New Scene")) {}
            if (ImGui::MenuItem("Open Scene")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Save ")) {
                SceneSerializer::Serialize("C:/Users/paulz/OneDrive/Desktop/MyScene.scene");
            }
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