#pragma once
#include <vector>
#include <functional>
#include <memory>
#include "EditorWindow.h"

class EditorWindowRegistry {
public:
    using Factory = std::function<std::unique_ptr<EditorWindow>()>;

    static EditorWindowRegistry& Instance() {
        static EditorWindowRegistry instance;
        return instance;
    }

    void Register(Factory factory) {
        factories.push_back(std::move(factory));
    }

    std::vector<std::unique_ptr<EditorWindow>> CreateAll() {
        std::vector<std::unique_ptr<EditorWindow>> windows;
        for (auto& f : factories)
            windows.push_back(f());
        return windows;
    }

private:
    std::vector<Factory> factories;
};