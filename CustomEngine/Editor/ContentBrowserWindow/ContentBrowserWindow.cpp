#include "ContentBrowserWindow.h"
#include "EditorWindow.h"
#include "EditorMacro.h"
#include "imgui.h"
#include <algorithm>
#include "../../src/Importers/Resources.h"
#include "../../src/Assets/Texture2D.h"
#include "../../src/Project/ProjectSettings.h"


ContentBrowserWindow::ContentBrowserWindow(): EditorWindow("ContentBrowser")
{
    m_currentDirectory = ProjectSettings::Get().GetRootPath();
}

void ContentBrowserWindow::Draw() {
    if (!BeginWindow()) return;

    float padding = 16.0f;
    float thumbnailSize = 64;
    float cellSize = padding + thumbnailSize;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = std::max(1, (int)(panelWidth / cellSize));

    auto folderIcon = Resources::Load<Texture2D>("engine://Editor/Icons/gray-folder-icon.png");
    auto fileIcon = Resources::Load<Texture2D>("engine://Editor/Icons/document-icon.png");

    ImGui::Columns(columnCount, 0, false);

    for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
    {
        const auto path = directoryEntry.path();
        std::string fileName = path.filename().string();

        auto& icon = directoryEntry.is_directory() ? folderIcon : fileIcon;
        
        ImGui::ImageButton(fileName.c_str(), (void*)(intptr_t)icon->ID, { thumbnailSize, thumbnailSize },
                               ImVec2(0, 1), ImVec2(1, 0));

        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
        {
            if (directoryEntry.is_directory())
            {
                m_currentDirectory /= path.filename();
            }
        }

        float textWidth = ImGui::CalcTextSize(fileName.c_str()).x;
        float offset = (thumbnailSize - textWidth + padding) * 0.5f;
        if (offset > 0.0f)
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offset);

        ImGui::Text("%s", fileName.c_str());

        ImGui::NextColumn();
    }

    ImGui::Columns(1);

    ImGui::End();
}

REGISTER_EDITOR_WINDOW(ContentBrowserWindow)
