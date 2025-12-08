#pragma once
#include <string>

class Asset
{
public:
    std::string path;
    virtual ~Asset() = default;
};
