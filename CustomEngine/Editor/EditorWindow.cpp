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
