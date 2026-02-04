#pragma once
#include "IInputDevice.h"
#include "ButtonControll.h"
#include "Key.h"
#include <unordered_map>
#include <unordered_set>

class Keyboard : public IInputDevice {
public:
    void Init() override;
    void Update() override;
    void ProcessEvent(const SDL_Event* e) override;

    // Alphabet keys
    ButtonControll& aKey() { return (*this)[Key::A]; }
    ButtonControll& bKey() { return (*this)[Key::B]; }
    ButtonControll& cKey() { return (*this)[Key::C]; }
    ButtonControll& dKey() { return (*this)[Key::D]; }
    ButtonControll& eKey() { return (*this)[Key::E]; }
    ButtonControll& fKey() { return (*this)[Key::F]; }
    ButtonControll& gKey() { return (*this)[Key::G]; }
    ButtonControll& hKey() { return (*this)[Key::H]; }
    ButtonControll& iKey() { return (*this)[Key::I]; }
    ButtonControll& jKey() { return (*this)[Key::J]; }
    ButtonControll& kKey() { return (*this)[Key::K]; }
    ButtonControll& lKey() { return (*this)[Key::L]; }
    ButtonControll& mKey() { return (*this)[Key::M]; }
    ButtonControll& nKey() { return (*this)[Key::N]; }
    ButtonControll& oKey() { return (*this)[Key::O]; }
    ButtonControll& pKey() { return (*this)[Key::P]; }
    ButtonControll& qKey() { return (*this)[Key::Q]; }
    ButtonControll& rKey() { return (*this)[Key::R]; }
    ButtonControll& sKey() { return (*this)[Key::S]; }
    ButtonControll& tKey() { return (*this)[Key::T]; }
    ButtonControll& uKey() { return (*this)[Key::U]; }
    ButtonControll& vKey() { return (*this)[Key::V]; }
    ButtonControll& wKey() { return (*this)[Key::W]; }
    ButtonControll& xKey() { return (*this)[Key::X]; }
    ButtonControll& yKey() { return (*this)[Key::Y]; }
    ButtonControll& zKey() { return (*this)[Key::Z]; }

    // Number keys (top row)
    ButtonControll& num0Key() { return (*this)[Key::Num0]; }
    ButtonControll& num1Key() { return (*this)[Key::Num1]; }
    ButtonControll& num2Key() { return (*this)[Key::Num2]; }
    ButtonControll& num3Key() { return (*this)[Key::Num3]; }
    ButtonControll& num4Key() { return (*this)[Key::Num4]; }
    ButtonControll& num5Key() { return (*this)[Key::Num5]; }
    ButtonControll& num6Key() { return (*this)[Key::Num6]; }
    ButtonControll& num7Key() { return (*this)[Key::Num7]; }
    ButtonControll& num8Key() { return (*this)[Key::Num8]; }
    ButtonControll& num9Key() { return (*this)[Key::Num9]; }

    // Function keys
    ButtonControll& f1Key() { return (*this)[Key::F1]; }
    ButtonControll& f2Key() { return (*this)[Key::F2]; }
    ButtonControll& f3Key() { return (*this)[Key::F3]; }
    ButtonControll& f4Key() { return (*this)[Key::F4]; }
    ButtonControll& f5Key() { return (*this)[Key::F5]; }
    ButtonControll& f6Key() { return (*this)[Key::F6]; }
    ButtonControll& f7Key() { return (*this)[Key::F7]; }
    ButtonControll& f8Key() { return (*this)[Key::F8]; }
    ButtonControll& f9Key() { return (*this)[Key::F9]; }
    ButtonControll& f10Key() { return (*this)[Key::F10]; }
    ButtonControll& f11Key() { return (*this)[Key::F11]; }
    ButtonControll& f12Key() { return (*this)[Key::F12]; }

    // Control keys
    ButtonControll& escapeKey() { return (*this)[Key::Escape]; }
    ButtonControll& tabKey() { return (*this)[Key::Tab]; }
    ButtonControll& capsLockKey() { return (*this)[Key::CapsLock]; }
    ButtonControll& leftShiftKey() { return (*this)[Key::LeftShift]; }
    ButtonControll& rightShiftKey() { return (*this)[Key::RightShift]; }
    ButtonControll& leftCtrlKey() { return (*this)[Key::LeftCtrl]; }
    ButtonControll& rightCtrlKey() { return (*this)[Key::RightCtrl]; }
    ButtonControll& leftAltKey() { return (*this)[Key::LeftAlt]; }
    ButtonControll& rightAltKey() { return (*this)[Key::RightAlt]; }
    ButtonControll& spaceKey() { return (*this)[Key::Space]; }
    ButtonControll& enterKey() { return (*this)[Key::Enter]; }
    ButtonControll& backspaceKey() { return (*this)[Key::Backspace]; }
    ButtonControll& insertKey() { return (*this)[Key::Insert]; }
    ButtonControll& deleteKey() { return (*this)[Key::Delete]; }
    ButtonControll& homeKey() { return (*this)[Key::Home]; }
    ButtonControll& endKey() { return (*this)[Key::End]; }
    ButtonControll& pageUpKey() { return (*this)[Key::PageUp]; }
    ButtonControll& pageDownKey() { return (*this)[Key::PageDown]; }

    // Arrow keys
    ButtonControll& arrowUpKey() { return (*this)[Key::Up]; }
    ButtonControll& arrowDownKey() { return (*this)[Key::Down]; }
    ButtonControll& arrowLeftKey() { return (*this)[Key::Left]; }
    ButtonControll& arrowRightKey() { return (*this)[Key::Right]; }

    // Numpad keys
    ButtonControll& numpad0Key() { return (*this)[Key::Numpad0]; }
    ButtonControll& numpad1Key() { return (*this)[Key::Numpad1]; }
    ButtonControll& numpad2Key() { return (*this)[Key::Numpad2]; }
    ButtonControll& numpad3Key() { return (*this)[Key::Numpad3]; }
    ButtonControll& numpad4Key() { return (*this)[Key::Numpad4]; }
    ButtonControll& numpad5Key() { return (*this)[Key::Numpad5]; }
    ButtonControll& numpad6Key() { return (*this)[Key::Numpad6]; }
    ButtonControll& numpad7Key() { return (*this)[Key::Numpad7]; }
    ButtonControll& numpad8Key() { return (*this)[Key::Numpad8]; }
    ButtonControll& numpad9Key() { return (*this)[Key::Numpad9]; }
    ButtonControll& numpadEnterKey() { return (*this)[Key::NumpadEnter]; }
    ButtonControll& numpadPlusKey() { return (*this)[Key::NumpadPlus]; }
    ButtonControll& numpadMinusKey() { return (*this)[Key::NumpadMinus]; }
    ButtonControll& numpadMultiplyKey() { return (*this)[Key::NumpadMultiply]; }
    ButtonControll& numpadDivideKey() { return (*this)[Key::NumpadDivide]; }
    ButtonControll& numpadDotKey() { return (*this)[Key::NumpadDot]; }

    // Symbols / punctuation
    ButtonControll& minusKey() { return (*this)[Key::Minus]; }
    ButtonControll& equalKey() { return (*this)[Key::Equal]; }
    ButtonControll& leftBracketKey() { return (*this)[Key::LeftBracket]; }
    ButtonControll& rightBracketKey() { return (*this)[Key::RightBracket]; }
    ButtonControll& backslashKey() { return (*this)[Key::Backslash]; }
    ButtonControll& semicolonKey() { return (*this)[Key::Semicolon]; }
    ButtonControll& apostropheKey() { return (*this)[Key::Apostrophe]; }
    ButtonControll& graveKey() { return (*this)[Key::Grave]; }
    ButtonControll& commaKey() { return (*this)[Key::Comma]; }
    ButtonControll& periodKey() { return (*this)[Key::Period]; }
    ButtonControll& slashKey() { return (*this)[Key::Slash]; }

    // Misc
    ButtonControll& printScreenKey() { return (*this)[Key::PrintScreen]; }
    ButtonControll& scrollLockKey() { return (*this)[Key::ScrollLock]; }
    ButtonControll& pauseKey() { return (*this)[Key::Pause]; }
    ButtonControll& menuKey() { return (*this)[Key::Menu]; }
    ButtonControll& leftWindowsKey() { return (*this)[Key::LeftWindows]; }
    ButtonControll& rightWindowsKey() { return (*this)[Key::RightWindows]; }


    ButtonControll& operator[](Key k)
    {
        return keys[k];
    }

private:
    std::unordered_map<Key, ButtonControll> keys;
    std::unordered_map<SDL_Keycode, Key> sdlMapping;
};
