#include "EditorStyle.h"
#include "imgui.h"

#include <filesystem>
#include <iostream>

void ApplyEditorStyle()
{
    ImGuiStyle& s = ImGui::GetStyle();
    ImVec4* c = s.Colors;

    // ---- Metrics: tight, slightly-rounded panels like the Unity editor ----
    s.WindowRounding    = 4.0f;
    s.ChildRounding     = 4.0f;
    s.FrameRounding     = 3.0f;
    s.PopupRounding     = 3.0f;
    s.GrabRounding      = 3.0f;
    s.TabRounding       = 3.0f;
    s.ScrollbarRounding = 3.0f;
    s.WindowPadding     = ImVec2(8.0f, 8.0f);
    s.FramePadding      = ImVec2(6.0f, 4.0f);
    s.ItemSpacing       = ImVec2(8.0f, 6.0f);
    s.ItemInnerSpacing  = ImVec2(6.0f, 4.0f);
    s.IndentSpacing     = 18.0f;
    s.ScrollbarSize     = 12.0f;
    s.GrabMinSize       = 10.0f;
    s.WindowBorderSize  = 1.0f;
    s.FrameBorderSize   = 0.0f;
    s.WindowMenuButtonPosition = ImGuiDir_None; // no collapse arrow in title bars

    // ---- Palette ----
    const ImVec4 bg       = ImVec4(0.18f, 0.18f, 0.18f, 1.00f); // window background
    const ImVec4 panel    = ImVec4(0.22f, 0.22f, 0.22f, 1.00f); // input frames
    const ImVec4 panelHi  = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
    const ImVec4 accent   = ImVec4(0.17f, 0.36f, 0.53f, 1.00f); // Unity selection blue
    const ImVec4 accentHi = ImVec4(0.22f, 0.45f, 0.66f, 1.00f);
    const ImVec4 dark     = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
    const ImVec4 border   = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

    c[ImGuiCol_Text]                 = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
    c[ImGuiCol_TextDisabled]         = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
    c[ImGuiCol_WindowBg]             = bg;
    c[ImGuiCol_ChildBg]              = bg;
    c[ImGuiCol_PopupBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    c[ImGuiCol_Border]               = border;
    c[ImGuiCol_BorderShadow]         = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    c[ImGuiCol_FrameBg]              = panel;
    c[ImGuiCol_FrameBgHovered]       = panelHi;
    // Grabbing a slider keeps the same background as hover — no color change on activate.
    c[ImGuiCol_FrameBgActive]        = panelHi;
    c[ImGuiCol_TitleBg]              = dark;
    c[ImGuiCol_TitleBgActive]        = dark;
    c[ImGuiCol_TitleBgCollapsed]     = dark;
    c[ImGuiCol_MenuBarBg]            = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
    c[ImGuiCol_ScrollbarBg]          = bg;
    c[ImGuiCol_ScrollbarGrab]        = panelHi;
    c[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.34f, 0.34f, 0.34f, 1.00f);
    c[ImGuiCol_ScrollbarGrabActive]  = accent;
    c[ImGuiCol_CheckMark]            = accentHi;
    c[ImGuiCol_SliderGrab]           = accentHi;
    c[ImGuiCol_SliderGrabActive]     = accent;
    c[ImGuiCol_Button]               = panel;
    c[ImGuiCol_ButtonHovered]        = panelHi;
    c[ImGuiCol_ButtonActive]         = accent;
    c[ImGuiCol_Header]               = panelHi;   // CollapsingHeader / Selectable
    c[ImGuiCol_HeaderHovered]        = accentHi;
    c[ImGuiCol_HeaderActive]         = accent;
    c[ImGuiCol_Separator]            = border;
    c[ImGuiCol_SeparatorHovered]     = accentHi;
    c[ImGuiCol_SeparatorActive]      = accent;
    c[ImGuiCol_Tab]                  = dark;
    c[ImGuiCol_TabHovered]           = accentHi;
    c[ImGuiCol_TabSelected]          = panelHi;
    c[ImGuiCol_TabDimmed]            = dark;
    c[ImGuiCol_TabDimmedSelected]    = panel;
    c[ImGuiCol_TableHeaderBg]        = panel;
    c[ImGuiCol_TableBorderStrong]    = border;
    c[ImGuiCol_TableBorderLight]     = ImVec4(0.16f, 0.16f, 0.16f, 1.00f);
    c[ImGuiCol_TableRowBg]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    c[ImGuiCol_TableRowBgAlt]        = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);
    c[ImGuiCol_TextSelectedBg]       = accent;
    c[ImGuiCol_DragDropTarget]       = accentHi;
    c[ImGuiCol_NavHighlight]         = accentHi;
}

static bool TryLoadFont(ImGuiIO& io, const char* path, float sizePx, const char* label)
{
    if (!std::filesystem::exists(path))
        return false;

    if (io.Fonts->AddFontFromFileTTF(path, sizePx) != nullptr)
    {
        std::cout << "[EditorStyle] Loaded " << label << " font: " << path << std::endl;
        return true;
    }
    return false;
}

void LoadEditorFonts(float sizePx)
{
    ImGuiIO& io = ImGui::GetIO();

    // 1) A font bundled with the project (drop any of these into Assets/Fonts/).
    const char* bundled[] = {
        "Assets/Fonts/Roboto-Regular.ttf",
        "Assets/Fonts/Inter-Regular.ttf",
        "Assets/Fonts/OpenSans-Regular.ttf",
    };
    for (const char* path : bundled)
        if (TryLoadFont(io, path, sizePx, "bundled"))
            return;

    // 2) A Windows system font (Segoe UI reads like a modern editor UI).
    const char* system[] = {
        "C:/Windows/Fonts/segoeui.ttf",
        "C:/Windows/Fonts/tahoma.ttf",
    };
    for (const char* path : system)
        if (TryLoadFont(io, path, sizePx, "system"))
            return;

    // 3) Fall back to ImGui's built-in font so the UI always renders.
    io.Fonts->AddFontDefault();
    std::cout << "[EditorStyle] Using default ImGui font." << std::endl;
}
