#pragma once
#include "imgui.h"

class EditorWindow {
protected:
    const char* windowName;

    bool BeginWindow();

public:
    bool open = true;

    EditorWindow(const char* name);
    virtual ~EditorWindow();
    const char* GetName();
    virtual void Draw() = 0;
};
