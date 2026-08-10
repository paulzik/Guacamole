#include "ContentBrowserWindow.h"
#include "EditorWindow.h"
#include "EditorMacro.h"
#include "imgui.h"
#include <algorithm>
#include "../../src/Importers/Resources.h"
#include "../../src/Assets/Texture2D.h"
#include "../../src/Project/ProjectSettings.h"
#include <iostream>

ContentBrowserWindow::ContentBrowserWindow(): EditorWindow("ContentBrowser")
{
    m_currentDirectory = ProjectSettings::Get().GetRootPath() / "Assets";

    icon_mapper[""] = Resources::Load<Texture2D>("engine://Editor/Icons/gray-folder-icon.png");
    icon_mapper["doc"] = Resources::Load<Texture2D>("engine://Editor/Icons/document-icon.png");
}

void ContentBrowserWindow::Draw() {
    if (!BeginWindow()) return;

    std::filesystem::path assetsRoot = ProjectSettings::Get().GetRootPath() / "Assets";
    auto relativePath = std::filesystem::relative(m_currentDirectory, assetsRoot);

    struct Crumb { std::string name; std::filesystem::path path; };
    std::vector<Crumb> crumbs{ { "Assets", assetsRoot } };

    if (relativePath != ".")
    {
        std::filesystem::path accumulated = assetsRoot;
        for (const auto& part : relativePath)
        {
            accumulated /= part;
            crumbs.push_back({ part.string(), accumulated });
        }
    }

    for (size_t i = 0; i < crumbs.size(); ++i)
    {
        if (i > 0)
        {
            ImGui::SameLine();
            ImGui::AlignTextToFramePadding();
            ImGui::Text(">");
            ImGui::SameLine();
        }

        if (i + 1 == crumbs.size())
        {
            ImGui::AlignTextToFramePadding();
            ImGui::Text("%s", crumbs[i].name.c_str());
        }
        else if (ImGui::Button(crumbs[i].name.c_str()))
            m_currentDirectory = crumbs[i].path;
    }

    ImGui::Separator();

    if (!std::filesystem::exists(m_currentDirectory))
    {
        ImGui::TextDisabled("This project has no Assets folder yet.");
        ImGui::End();
        return;
    }

    float padding = 16.0f;
    float thumbnailSize = 64;
    float cellSize = padding + thumbnailSize;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = std::max(1, (int)(panelWidth / cellSize));

    ImGui::Columns(columnCount, 0, false);

    for (auto& directoryEntry : std::filesystem::directory_iterator(m_currentDirectory))
    {
        const auto path = directoryEntry.path();
        std::string fileName = path.filename().string();

        auto& icon = directoryEntry.is_directory() ? icon_mapper[""] : icon_mapper["doc"];
        
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
