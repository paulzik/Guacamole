#pragma once
#include "EditorRegistry.h"
#include "EditorWindowRegistry.h"

#define CUSTOM_EDITOR(ComponentType, EditorType) \
    namespace { \
        struct EditorType##_##ComponentType##_AutoRegister { \
            EditorType##_##ComponentType##_AutoRegister() { \
                EditorRegistry::Instance().Register<ComponentType, EditorType>(); \
            } \
        } EditorType##_##ComponentType##_AutoRegister_Instance; \
    }

#define REGISTER_EDITOR_WINDOW(WindowType, ...) \
    namespace { \
        struct WindowType##_AutoRegister { \
            WindowType##_AutoRegister() { \
                EditorWindowRegistry::Instance().Register( \
                    []() -> std::unique_ptr<EditorWindow> { \
                        return std::make_unique<WindowType>(__VA_ARGS__); \
                    }); \
            } \
        } WindowType##_AutoRegister_Instance; \
    }