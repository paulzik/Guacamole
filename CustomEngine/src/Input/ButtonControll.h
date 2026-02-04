#pragma once

class ButtonControll{
public:
    bool isDown = false;        // current state
    bool prevIsDown = false;    // previous frame

    bool wasPressedThisFrame = false;
    bool wasReleasedThisFrame = false;
};
