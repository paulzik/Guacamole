#include "Mouse.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_mouse.h>
#include "Input.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <iostream>

void Mouse::Init()
{

}

void Mouse::Update()
{
    auto updateButton = [](ButtonControll& b) 
        {
            b.wasPressedThisFrame = (!b.prevIsDown && b.isDown);
            b.wasReleasedThisFrame = (b.prevIsDown && !b.isDown);

            b.prevIsDown = b.isDown;
        };

    updateButton(leftButton);
    updateButton(rightButton);
    updateButton(middleButton);
}

void Mouse::ProcessEvent(const SDL_Event* e) {
    if (e->type == SDL_EVENT_MOUSE_WHEEL) {
        //std::cout << "MOUSE WHEEL" << std::endl;
        scrollWheel.value.x = static_cast<float>(e->wheel.x);
        scrollWheel.value.y = static_cast<float>(e->wheel.y);

        scrollWheel.up = scrollWheel.value.y > 0;
        scrollWheel.down = scrollWheel.value.y < 0;
        scrollWheel.left = scrollWheel.value.x < 0;
        scrollWheel.right = scrollWheel.value.x > 0;

    }
    else if (e->type == SDL_EVENT_MOUSE_MOTION) {
        position.x = e->motion.x;
        position.y = e->motion.y;
    }
    else if (e->type == SDL_EVENT_MOUSE_BUTTON_DOWN)
    {
        const SDL_MouseButtonEvent& btn = e->button;

        if (btn.button == SDL_BUTTON_LEFT)   leftButton.isDown = true;
        if (btn.button == SDL_BUTTON_RIGHT)  rightButton.isDown = true;
        if (btn.button == SDL_BUTTON_MIDDLE) middleButton.isDown = true;
    }
    else if (e->type == SDL_EVENT_MOUSE_BUTTON_UP)
    {
        const SDL_MouseButtonEvent& btn = e->button;

        if (btn.button == SDL_BUTTON_LEFT)   leftButton.isDown = false;
        if (btn.button == SDL_BUTTON_RIGHT)  rightButton.isDown = false;
        if (btn.button == SDL_BUTTON_MIDDLE) middleButton.isDown = false;
    }
}
