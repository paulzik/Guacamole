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
    // Poll SDL events
    scrollWheel.prevValue = scrollWheel.value;  // save previous frame
    scrollWheel.value = glm::vec2(0.0f);   // reset for this frame

    // compute delta
    scrollWheel.delta = scrollWheel.value - scrollWheel.prevValue;

    // compute digital directions
    scrollWheel.up = scrollWheel.value.y > 0;
    scrollWheel.down = scrollWheel.value.y < 0;
    scrollWheel.left = scrollWheel.value.x < 0;
    scrollWheel.right = scrollWheel.value.x > 0;

    // per-frame movement flag
    scrollWheel.wasMovedThisFrame = scrollWheel.delta != glm::vec2(0.0f);

    // save previous states
    leftButton.prevIsPressed = leftButton.isPressed;
    rightButton.prevIsPressed = rightButton.isPressed;
    middleButton.prevIsPressed = middleButton.isPressed;

    // Get current mouse state
    Uint32 buttons = SDL_GetMouseState(&position.x, &position.y);
    leftButton.isPressed = buttons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT);
    middleButton.isPressed = buttons & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE);
    rightButton.isPressed = buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT);

    leftButton.wasPressedThisFrame = leftButton.isPressed && !leftButton.prevIsPressed;
    leftButton.wasReleasedThisFrame = !leftButton.isPressed && leftButton.prevIsPressed;

    middleButton.wasPressedThisFrame = middleButton.isPressed && !middleButton.prevIsPressed;
    middleButton.wasReleasedThisFrame = !middleButton.isPressed && middleButton.prevIsPressed;

    rightButton.wasPressedThisFrame = rightButton.isPressed && !rightButton.prevIsPressed;
    rightButton.wasReleasedThisFrame = !rightButton.isPressed && rightButton.prevIsPressed;

    leftButton.isReleased = !leftButton.isPressed;
    middleButton.isReleased = !middleButton.isPressed;
    rightButton.isReleased = !rightButton.isPressed;
}

void Mouse::ProcessEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_MOUSE_WHEEL) {
        scrollWheel.value.x = static_cast<float>(e.wheel.x);
        scrollWheel.value.y = static_cast<float>(e.wheel.y);
    }
}
