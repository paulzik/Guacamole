#pragma once

#define COMPONENT_NAME(type)                      \
public:                                          \
    static constexpr const char* StaticName()     \
    { return #type; }                             \
    const char* GetComponentName() const override \
    { return StaticName(); }