#pragma once
#include "EditorWindow.h"
#include <filesystem>

class ContentBrowserWindow : public EditorWindow {
public:
    ContentBrowserWindow();
    void Draw() override;

private:
    std::filesystem::path m_currentDirectory;

};