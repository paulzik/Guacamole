#pragma once
#include "EditorWindow.h"
#include <vector>
#include <memory>

class MenuBar : public EditorWindow {
    std::vector<std::unique_ptr<EditorWindow>>* windows;
public:
    MenuBar(std::vector<std::unique_ptr<EditorWindow>>* windows);
    void Draw() override;
};