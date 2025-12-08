#pragma once
#include "Asset.h"
#include <GL/glew.h>

class Texture2D : public Asset
{
public:
    GLuint ID = 0;
    int width = 0;
    int height = 0;

    virtual ~Texture2D() {
        if (ID) glDeleteTextures(1, &ID);
    }
};
