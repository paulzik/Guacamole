#pragma once
#include "EditorRegistry.h"

#define CUSTOM_EDITOR(ComponentType, EditorType) \
    namespace { \
        struct EditorType##_AutoRegister { \
            EditorType##_AutoRegister() { \
                EditorRegistry::Instance().Register<ComponentType, EditorType>(); \
            } \
        } EditorType##_AutoRegister_Instance; \
    }
