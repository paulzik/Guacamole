#pragma once

// Unity-inspired editor look-and-feel for Dear ImGui.
// Call both, once, after ImGui::CreateContext() and before the main loop.

// Applies a dark theme (colors, rounding, spacing) to the current ImGui context.
void ApplyEditorStyle();

// Loads a modern UI font into the ImGui atlas, with graceful fallbacks:
//   1) a bundled TTF under Assets/Fonts/
//   2) a Windows system font (Segoe UI)
//   3) ImGui's built-in font
void LoadEditorFonts(float sizePx = 16.0f);
