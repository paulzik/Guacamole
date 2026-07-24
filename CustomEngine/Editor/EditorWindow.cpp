#include "EditorWindow.h"

EditorWindow::EditorWindow(const char* name)
    : windowName(name)
{
}

EditorWindow::~EditorWindow()
{
}

const char* EditorWindow::GetName()
{
    return windowName;
}

bool EditorWindow::BeginWindow() {
    if (!open) return false;

    ImGui::Begin(windowName, &open);
    return true;
}
