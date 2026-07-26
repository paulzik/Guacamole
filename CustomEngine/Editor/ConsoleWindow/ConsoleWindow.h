#pragma once
#include "EditorWindow.h"

class ConsoleWindow : public EditorWindow {
public:
    ConsoleWindow();
    void Draw() override;

private:

    bool showLogs = true;
    bool showWarnings = true;
    bool showErrors = true;
};