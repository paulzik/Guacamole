#include "ShaderImporter.h"
#include <assimp/Importer.hpp>
#include "ShaderSource.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

std::shared_ptr<Asset> ShaderImporter::Load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader: " << path << std::endl;
        return nullptr;
    }

    std::stringstream ss;
    ss << file.rdbuf();
    file.close();

    auto shaderAsset = std::make_shared<ShaderSource>();
    shaderAsset->path = path;
    shaderAsset->sourceCode = ss.str();

    if (path.ends_with(".vert"))
        shaderAsset->type = ShaderSource::ShaderType::Vertex;
    else
        shaderAsset->type = ShaderSource::ShaderType::Fragment;

    return shaderAsset;
}