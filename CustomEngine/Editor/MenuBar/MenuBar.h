#pragma once
#include "EditorWindow.h"
#include <vector>
#include <memory>
#include <string>
#include <filesystem>

struct SDL_Window;

class MenuBar : public EditorWindow {
    std::vector<std::unique_ptr<EditorWindow>>* windows;
    SDL_Window* sdlWindow;

    std::filesystem::path currentScenePath;

public:
    MenuBar(std::vector<std::unique_ptr<EditorWindow>>* windows, SDL_Window* sdlWindow);
    void Draw() override;

    bool HandleEvent(const union SDL_Event& event);
};
