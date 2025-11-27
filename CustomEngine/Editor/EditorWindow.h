#pragma once

class EditorWindow {
protected:
    const char* windowName;

public:
    EditorWindow(const char* name);
    virtual ~EditorWindow();

    virtual void Draw() = 0;
};
