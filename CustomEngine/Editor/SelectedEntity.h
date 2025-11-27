#pragma once
#include "ECS/Entity.h"

class SelectedEntity {
protected:
    static Entity* selected;

public:
    static void Set(Entity* e);
    static Entity* Get();
};
