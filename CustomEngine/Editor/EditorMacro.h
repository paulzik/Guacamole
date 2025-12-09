#pragma once
#include "EditorRegistry.h"

#define CUSTOM_EDITOR(ComponentType, EditorType) \
    namespace { \
        struct EditorType##_##ComponentType##_AutoRegister { \
            EditorType##_##ComponentType##_AutoRegister() { \
                EditorRegistry::Instance().Register<ComponentType, EditorType>(); \
            } \
        } EditorType##_##ComponentType##_AutoRegister_Instance; \
    }
