#include "Keyboard.h"

void Keyboard::Init()
{
    // Alphabet
    sdlMapping[SDLK_A] = Key::A;
    sdlMapping[SDLK_B] = Key::B;
    sdlMapping[SDLK_C] = Key::C;
    sdlMapping[SDLK_D] = Key::D;
    sdlMapping[SDLK_E] = Key::E;
    sdlMapping[SDLK_D] = Key::F;
    sdlMapping[SDLK_G] = Key::G;
    sdlMapping[SDLK_H] = Key::H;
    sdlMapping[SDLK_I] = Key::I;
    sdlMapping[SDLK_J] = Key::J;
    sdlMapping[SDLK_K] = Key::K;
    sdlMapping[SDLK_L] = Key::L;
    sdlMapping[SDLK_M] = Key::M;
    sdlMapping[SDLK_N] = Key::N;
    sdlMapping[SDLK_O] = Key::O;
    sdlMapping[SDLK_P] = Key::P;
    sdlMapping[SDLK_Q] = Key::Q;
    sdlMapping[SDLK_R] = Key::R;
    sdlMapping[SDLK_S] = Key::S;
    sdlMapping[SDLK_T] = Key::T;
    sdlMapping[SDLK_U] = Key::U;
    sdlMapping[SDLK_V] = Key::V;
    sdlMapping[SDLK_W] = Key::W;
    sdlMapping[SDLK_X] = Key::X;
    sdlMapping[SDLK_Y] = Key::Y;
    sdlMapping[SDLK_Z] = Key::Z;

    // Numbers (top row)
    sdlMapping[SDLK_0] = Key::Num0;
    sdlMapping[SDLK_1] = Key::Num1;
    sdlMapping[SDLK_2] = Key::Num2;
    sdlMapping[SDLK_3] = Key::Num3;
    sdlMapping[SDLK_4] = Key::Num4;
    sdlMapping[SDLK_5] = Key::Num5;
    sdlMapping[SDLK_6] = Key::Num6;
    sdlMapping[SDLK_7] = Key::Num7;
    sdlMapping[SDLK_8] = Key::Num8;
    sdlMapping[SDLK_9] = Key::Num9;

    // Function keys
    sdlMapping[SDLK_F1] = Key::F1;
    sdlMapping[SDLK_F2] = Key::F2;
    sdlMapping[SDLK_F3] = Key::F3;
    sdlMapping[SDLK_F4] = Key::F4;
    sdlMapping[SDLK_F5] = Key::F5;
    sdlMapping[SDLK_F6] = Key::F6;
    sdlMapping[SDLK_F7] = Key::F7;
    sdlMapping[SDLK_F8] = Key::F8;
    sdlMapping[SDLK_F9] = Key::F9;
    sdlMapping[SDLK_F10] = Key::F10;
    sdlMapping[SDLK_F11] = Key::F11;
    sdlMapping[SDLK_F12] = Key::F12;

    // Control keys
    sdlMapping[SDLK_ESCAPE] = Key::Escape;
    sdlMapping[SDLK_TAB] = Key::Tab;
    sdlMapping[SDLK_CAPSLOCK] = Key::CapsLock;
    sdlMapping[SDLK_LSHIFT] = Key::LeftShift;
    sdlMapping[SDLK_RSHIFT] = Key::RightShift;
    sdlMapping[SDLK_LCTRL] = Key::LeftCtrl;
    sdlMapping[SDLK_RCTRL] = Key::RightCtrl;
    sdlMapping[SDLK_LALT] = Key::LeftAlt;
    sdlMapping[SDLK_RALT] = Key::RightAlt;
    sdlMapping[SDLK_SPACE] = Key::Space;
    sdlMapping[SDLK_RETURN] = Key::Enter;
    sdlMapping[SDLK_BACKSPACE] = Key::Backspace;
    sdlMapping[SDLK_INSERT] = Key::Insert;
    sdlMapping[SDLK_DELETE] = Key::Delete;
    sdlMapping[SDLK_HOME] = Key::Home;
    sdlMapping[SDLK_END] = Key::End;
    sdlMapping[SDLK_PAGEUP] = Key::PageUp;
    sdlMapping[SDLK_PAGEDOWN] = Key::PageDown;

    // Arrow keys
    sdlMapping[SDLK_UP] = Key::Up;
    sdlMapping[SDLK_DOWN] = Key::Down;
    sdlMapping[SDLK_LEFT] = Key::Left;
    sdlMapping[SDLK_RIGHT] = Key::Right;

    // Numpad keys
    sdlMapping[SDLK_KP_0] = Key::Numpad0;
    sdlMapping[SDLK_KP_1] = Key::Numpad1;
    sdlMapping[SDLK_KP_2] = Key::Numpad2;
    sdlMapping[SDLK_KP_3] = Key::Numpad3;
    sdlMapping[SDLK_KP_4] = Key::Numpad4;
    sdlMapping[SDLK_KP_5] = Key::Numpad5;
    sdlMapping[SDLK_KP_6] = Key::Numpad6;
    sdlMapping[SDLK_KP_7] = Key::Numpad7;
    sdlMapping[SDLK_KP_8] = Key::Numpad8;
    sdlMapping[SDLK_KP_9] = Key::Numpad9;
    sdlMapping[SDLK_KP_ENTER] = Key::NumpadEnter;
    sdlMapping[SDLK_KP_PLUS] = Key::NumpadPlus;
    sdlMapping[SDLK_KP_MINUS] = Key::NumpadMinus;
    sdlMapping[SDLK_KP_MULTIPLY] = Key::NumpadMultiply;
    sdlMapping[SDLK_KP_DIVIDE] = Key::NumpadDivide;
    sdlMapping[SDLK_KP_PERIOD] = Key::NumpadDot;

    // Symbols / punctuation
    sdlMapping[SDLK_MINUS] = Key::Minus;
    sdlMapping[SDLK_EQUALS] = Key::Equal;
    sdlMapping[SDLK_LEFTBRACKET] = Key::LeftBracket;
    sdlMapping[SDLK_RIGHTBRACKET] = Key::RightBracket;
    sdlMapping[SDLK_BACKSLASH] = Key::Backslash;
    sdlMapping[SDLK_SEMICOLON] = Key::Semicolon;
    sdlMapping[SDLK_APOSTROPHE] = Key::Apostrophe;
    sdlMapping[SDLK_GRAVE] = Key::Grave;
    sdlMapping[SDLK_COMMA] = Key::Comma;
    sdlMapping[SDLK_PERIOD] = Key::Period;
    sdlMapping[SDLK_SLASH] = Key::Slash;

    // Misc
    sdlMapping[SDLK_PRINTSCREEN] = Key::PrintScreen;
    sdlMapping[SDLK_SCROLLLOCK] = Key::ScrollLock;
    sdlMapping[SDLK_PAUSE] = Key::Pause;
    sdlMapping[SDLK_MENU] = Key::Menu;
    sdlMapping[SDLK_LGUI] = Key::LeftWindows;
    sdlMapping[SDLK_RGUI] = Key::RightWindows;
}


void Keyboard::Update()
{
    auto updateKey = [](ButtonControll& b)
        {
            b.wasPressedThisFrame = (!b.prevIsDown && b.isDown);
            b.wasReleasedThisFrame = (b.prevIsDown && !b.isDown);

            b.prevIsDown = b.isDown;
        };

    for (auto& [key, btn] : keys)
        updateKey(btn);
}

void Keyboard::ProcessEvent(const SDL_Event* e)
{
    if (e->type != SDL_EVENT_KEY_DOWN && e->type != SDL_EVENT_KEY_UP)
        return;

    auto it = sdlMapping.find(e->key.key);
    if (it == sdlMapping.end()) return;

    Key k = it->second;
    ButtonControll& btn = keys[k];
    btn.isDown = (e->type == SDL_EVENT_KEY_DOWN);
}
