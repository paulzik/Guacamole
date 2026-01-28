#pragma once
#include "Collider.h"

class BoxCollider : public Collider {
public:

    BoxCollider(bool trigger, float size) : Collider(trigger) 
    {
        m_size = size;
    }

    ~BoxCollider() override
    {
        // cleanup Bullet shape if owned here
    }

private:
    float m_size;
};
