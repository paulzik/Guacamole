#pragma once

enum class Key
{
    Unknown,

    // Alphabet keys
    A, B, C, D, E, F, G, H, I, J, K, L, M,
    N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

    // Number keys (top row)
    Num0, Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9,

    // Function keys
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

    // Control keys
    Escape, Tab, CapsLock, LeftShift, RightShift,
    LeftCtrl, RightCtrl, LeftAlt, RightAlt,
    Space, Enter, Backspace, Insert, Delete,
    Home, End, PageUp, PageDown,

    // Arrow keys
    Up, Down, Left, Right,

    // Numpad keys
    Numpad0, Numpad1, Numpad2, Numpad3, Numpad4,
    Numpad5, Numpad6, Numpad7, Numpad8, Numpad9,
    NumpadEnter, NumpadPlus, NumpadMinus, NumpadMultiply, NumpadDivide, NumpadDot,

    // Symbols / punctuation
    Minus, Equal, LeftBracket, RightBracket, Backslash,
    Semicolon, Apostrophe, Grave, Comma, Period, Slash,

    // Misc
    PrintScreen, ScrollLock, Pause,
    Menu, LeftWindows, RightWindows
};

// Optional, usually not needed
inline bool operator==(Key lhs, Key rhs) {
    return static_cast<int>(lhs) == static_cast<int>(rhs);
}

inline bool operator!=(Key lhs, Key rhs) {
    return !(lhs == rhs);
}