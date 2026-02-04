#pragma once
#include "IInputDevice.h"
#include <vector>
#include <glm/vec2.hpp>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include <SDL3/SDL_events.h>

class Input {
public:
    template<typename T, typename... Args>
    static T& AddDevice(Args&&... args) {
        auto device = std::make_unique<T>(std::forward<Args>(args)...);
        T* ptr = device.get();
        devices[typeid(T)] = std::move(device);
        return *ptr;
    }

    template<typename T>
    static T* GetDevice()
    {
        auto it = devices.find(typeid(T));
        if (it != devices.end())
            return static_cast<T*>(it->second.get());
        return nullptr;
    }

    static void Init();
    static void Update();
    static bool SDL3_ProcessEvent(const SDL_Event* event);

private:
    static inline std::unordered_map<std::type_index, std::unique_ptr<IInputDevice>> devices;
    static inline glm::vec2 pointerPosition;
    static inline glm::vec2 pointerDelta;
};
