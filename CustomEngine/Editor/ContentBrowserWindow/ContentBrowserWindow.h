#pragma once
#include "EditorWindow.h"
#include "Assets/Texture2D.h"
#include <filesystem>
#include <unordered_map>
#include <string>
#include <memory>

class ContentBrowserWindow : public EditorWindow {
public:
    ContentBrowserWindow();
    void Draw() override;

private:
    std::filesystem::path m_currentDirectory;

    std::unordered_map<std::string, std::shared_ptr<Texture2D>> icon_mapper;
};