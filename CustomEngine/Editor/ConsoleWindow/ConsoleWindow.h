#pragma once
#include "EditorWindow.h"

class ConsoleWindow : public EditorWindow {
public:
    ConsoleWindow();
    void Draw() override;
};