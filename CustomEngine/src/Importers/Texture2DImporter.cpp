#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image.h"
#include "Texture2DImporter.h"
#include "Assets/Texture2D.h"
#include <iostream>
#include <memory>
#include <GL/glew.h>

std::shared_ptr<Asset> Texture2DImporter::Load(const std::string& path)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1); // optional: flip texture vertically
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 4); // force RGBA

    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        return nullptr;
    }

    auto texture = std::make_shared<Texture2D>();
    texture->width = width;
    texture->height = height;

    // Upload to GPU (assuming Texture2D has an OpenGL handle)
    glGenTextures(1, &texture->ID);
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Set some default texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);

    return texture;
}
