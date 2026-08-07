#pragma once
#include <string>

class Asset
{
public:
    std::string path;
    std::string name;

    virtual ~Asset() = default;

    virtual void OnPathAssigned() {}
};
