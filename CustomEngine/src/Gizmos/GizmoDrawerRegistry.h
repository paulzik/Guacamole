#pragma once
#include "ECS/Entity.h"
#include "Gizmos/IGizmoDrawer.h"
#include <unordered_map>
#include <typeindex>
#include <memory>

class GizmoDrawerRegistry {
public:
    static std::unordered_map<std::type_index, std::unique_ptr<IGizmoDrawer>>& GetRegistry() {
        static std::unordered_map<std::type_index, std::unique_ptr<IGizmoDrawer>> registry;
        return registry;
    }

    template<typename ComponentType, typename DrawerType>
    static void RegisterDrawer() {
        GetRegistry()[typeid(ComponentType)] = std::make_unique<DrawerType>();
    }
};

// Macro for registration
#define REGISTER_GIZMO_DRAWER(ComponentType, DrawerType) \
    namespace { \
        struct DrawerType##Registrator { \
            DrawerType##Registrator() { \
                GizmoDrawerRegistry::RegisterDrawer<ComponentType, DrawerType>(); \
            } \
        }; \
        static DrawerType##Registrator global_##DrawerType##Registrator; \
    }
