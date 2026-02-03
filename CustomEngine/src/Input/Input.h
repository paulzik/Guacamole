#pragma once
#include "IInputDevice.h"
#include <vector>
#include <glm/vec2.hpp>
#include <memory>
#include <unordered_map>
#include <typeindex>

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

    static glm::vec2 GetPointerPosition();
    static glm::vec2 GetPointerDelta();

    static void SetPointerPosition(glm::vec2 position);
    static void SetPointerDelta(glm::vec2 delta);
private:
    static inline std::unordered_map<std::type_index, std::unique_ptr<IInputDevice>> devices;

    static inline glm::vec2 pointerPosition;
    static inline glm::vec2 pointerDelta;
};
