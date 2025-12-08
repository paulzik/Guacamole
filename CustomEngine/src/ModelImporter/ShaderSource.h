#pragma once
#include "ShaderSource.h"
#include "ModelImporter/Asset.h"
#include <memory>
#include <string>

class ShaderSource : public Asset
{
public:
    std::string sourceCode;
    enum class ShaderType { Vertex, Fragment } type;
};