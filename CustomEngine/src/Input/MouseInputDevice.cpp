#include "MouseInputDevice.h"
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_mouse.h>
#include "Input.h"

void MouseInputDevice::Init()
{

}

void MouseInputDevice::Update()
{
    float x = 0.0f, y = 0.0f;
    Uint32 buttons = SDL_GetMouseState(&x, &y);

    glm::vec2 currentPos = { (float)x, (float)y };
    //glm::vec2 delta = { (float)(x - prevPosition.x), (float)(y - prevPosition.y) };

    Input::SetPointerPosition(currentPos);
    //Input::SetPointerDelta(delta);

    prevPosition.x = x;
    prevPosition.y = y;

    // You can also detect buttons here
    //Input::SetButton(SDL_BUTTON_LEFT, buttons & SDL_BUTTON_LEFT);
    //Input::SetButton(SDL_BUTTON_RIGHT, buttons & SDL_BUTTON_RIGHT);
}

glm::vec2 MouseInputDevice::GetPosition()
{
	return position;
}
