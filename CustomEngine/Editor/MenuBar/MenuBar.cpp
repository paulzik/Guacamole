#include "MenuBar.h"
#include "Scene/SceneSerializer.h"
#include "Project/ProjectSettings.h"
#include "Importers/Resources.h"
#include "ECS/Scene.h"
#include "Utilities/Debug/Debug.h"
#include <imgui.h>
#include <SDL3/SDL.h>
#include <filesystem>
#include <iostream>

static Uint32 s_openProjectEvent = 0;
static Uint32 s_openSceneEvent = 0;
static Uint32 s_saveSceneEvent = 0;

// Scene files only, so the picker does not offer to open a model or a texture.
static const SDL_DialogFileFilter s_sceneFilters[] = {
    { "Guacamole scene", "scene" },
    { "All files",       "*" }
};

MenuBar::MenuBar(std::vector<std::unique_ptr<EditorWindow>>* windows, SDL_Window* sdlWindow)
    : EditorWindow("MenuBar"), windows(windows), sdlWindow(sdlWindow)
{
    if (s_openProjectEvent == 0)
        s_openProjectEvent = SDL_RegisterEvents(1);

    if (s_openSceneEvent == 0)
        s_openSceneEvent = SDL_RegisterEvents(1);

    if (s_saveSceneEvent == 0)
        s_saveSceneEvent = SDL_RegisterEvents(1);
}

static void PushChosenPath(Uint32 eventType, const char* const* filelist)
{
    // SDL distinguishes three outcomes: null list = error, empty list = cancelled.
    if (!filelist || !filelist[0])
        return;

    SDL_Event event{};
    event.type = eventType;
    event.user.data1 = SDL_strdup(filelist[0]);
    SDL_PushEvent(&event);
}

static void OnFolderChosen(void* /*userdata*/, const char* const* filelist, int)
{
    PushChosenPath(s_openProjectEvent, filelist);
}

static void OnSceneChosen(void* /*userdata*/, const char* const* filelist, int)
{
    PushChosenPath(s_openSceneEvent, filelist);
}

static void OnSaveLocationChosen(void* /*userdata*/, const char* const* filelist, int)
{
    PushChosenPath(s_saveSceneEvent, filelist);
}

static std::filesystem::path EnsureSceneExtension(std::filesystem::path path)
{
    if (path.extension() != ".scene")
        path.replace_extension(".scene");
    return path;
}

bool MenuBar::HandleEvent(const SDL_Event& event)
{
    const bool isProject = (s_openProjectEvent != 0 && event.type == s_openProjectEvent);
    const bool isScene   = (s_openSceneEvent   != 0 && event.type == s_openSceneEvent);
    const bool isSaveAs  = (s_saveSceneEvent   != 0 && event.type == s_saveSceneEvent);

    if (!isProject && !isScene && !isSaveAs)
        return false;

    char* chosen = static_cast<char*>(event.user.data1);
    if (!chosen)
        return true;

    const std::filesystem::path selected = chosen;
    SDL_free(chosen);

    if (isSaveAs)
    {
        const std::filesystem::path target = EnsureSceneExtension(selected);
        if (SceneSerializer::Serialize(target))
            currentScenePath = target;
        return true;
    }

    if (isScene)
    {
        if (SceneSerializer::DeSerialize(selected))
            currentScenePath = selected;
        return true;
    }

    const std::filesystem::path folder = selected;

    if (!ProjectSettings::Get().Load(folder / "project.yaml"))
        ProjectSettings::Get().UseFolder(folder);

    Resources::SetBasePath(ProjectSettings::Get().GetRootPath());

    Debug::Log("Opened project '" + ProjectSettings::Get().GetName() +
               "' at " + ProjectSettings::Get().GetRootPath().generic_string());

    const std::filesystem::path startupScene = ProjectSettings::Get().GetStartupScene();

    if (startupScene.empty())
    {
        Debug::LogWarning("Project declares no StartupScene - starting empty");
        Scene::Get().Clear();
        currentScenePath.clear();
    }
    else
    {
        currentScenePath = ProjectSettings::Get().GetRootPath() / startupScene;
        SceneSerializer::DeSerialize(currentScenePath);
    }

    return true;
}

void MenuBar::Draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Project")) 
            {
                const std::string start = ProjectSettings::Get().GetRootPath().parent_path().string();
                SDL_ShowOpenFolderDialog(OnFolderChosen, this, sdlWindow, start.c_str(), false);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("New Scene")) {}
            if (ImGui::MenuItem("Open Scene")) 
            {
                const std::string start = (ProjectSettings::Get().GetRootPath() / "Assets").string();

                SDL_ShowOpenFileDialog(OnSceneChosen, this, sdlWindow,
                                       s_sceneFilters, SDL_arraysize(s_sceneFilters),
                                       start.c_str(), false);
            }
            if (ImGui::MenuItem("Clear Scene")) 
            {
                Scene::Get().Clear();
            }

            ImGui::Separator();

            if (ImGui::MenuItem("Save"))
            {
                const std::filesystem::path target = !currentScenePath.empty()
                    ? currentScenePath
                    : ProjectSettings::Get().GetRootPath() / ProjectSettings::Get().GetStartupScene();

                if (SceneSerializer::Serialize(target))
                    currentScenePath = target;
            }
            if (ImGui::MenuItem("Save As"))
            {
                const std::string start = (ProjectSettings::Get().GetRootPath() / "Assets").string();

                SDL_ShowSaveFileDialog(OnSaveLocationChosen, this, sdlWindow,
                                       s_sceneFilters, SDL_arraysize(s_sceneFilters),
                                       start.c_str());
            }
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