#include "Mouse.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_mouse.h>
#include "Input.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>

void Mouse::Init()
{

}

void Mouse::Update()
{
    // Reset scroll delta every frame
    scrollX = scrollY = 0;

    // Poll SDL events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EVENT_MOUSE_WHEEL) {
            scrollX = event.wheel.x;
            scrollY = event.wheel.y;
        }
    }

    // Get current mouse state
    Uint32 buttons = SDL_GetMouseState(&position.x, &position.y);
    left = buttons & SDL_BUTTON_MASK(SDL_BUTTON_LEFT);
    middle = buttons & SDL_BUTTON_MASK(SDL_BUTTON_MIDDLE);
    right = buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT);

    Input::SetPointerPosition(position);
}

glm::vec2 Mouse::GetPosition()
{
	return position;
}
