#pragma once
#include <glm/vec2.hpp>

class AxisControll{
public:
    glm::vec2 value;            // analog value (-1..1, or actual delta)
    glm::vec2 prevValue;        // previous frame value
    glm::vec2 delta;            // value - prevValue (optional, for per-frame change)

    bool up;                    // digital representation: value.y > 0
    bool down;                  // value.y < 0
    bool left;                  // value.x < 0
    bool right;                  // value.x > 0

    bool wasMovedThisFrame;     // optional: true if delta != 0
};
