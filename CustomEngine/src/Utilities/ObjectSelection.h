#pragma once
#include <cstdint>

using EntityID = uint32_t;

class ObjectSelection
{
public:
    static void Set(EntityID id) { s_Selected = id; }
    static EntityID Get() { return s_Selected; }
    static bool HasSelection() { return s_Selected != 0; }
    static void Clear() { s_Selected = 0; }

private:
    static inline EntityID s_Selected = 0;
};
