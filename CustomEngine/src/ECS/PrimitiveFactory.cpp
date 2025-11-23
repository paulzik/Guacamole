#include "PrimitiveFactory.h"

PrimitiveFactory::PrimitiveFactory() {

}

PrimitiveFactory::~PrimitiveFactory() {

}

MeshFilter PrimitiveFactory::CreateCubePrimitive(float size)
{
    float h = size * 0.5f;

    std::vector<Vertex> verts = {
        // Front face (+Z)
        {{-h,-h, h}, {1,0,0}, {0,0,1}},
        {{ h,-h, h}, {0,1,0}, {0,0,1}},
        {{ h, h, h}, {0,0,1}, {0,0,1}},
        {{-h, h, h}, {1,1,0}, {0,0,1}},

        // Back face (-Z)
        {{ h,-h,-h}, {1,0,1}, {0,0,-1}},
        {{-h,-h,-h}, {0,1,1}, {0,0,-1}},
        {{-h, h,-h}, {1,1,1}, {0,0,-1}},
        {{ h, h,-h}, {0,0,0}, {0,0,-1}},

        // Left face (-X)
        {{-h,-h,-h}, {1,0,0}, {-1,0,0}},
        {{-h,-h, h}, {0,1,0}, {-1,0,0}},
        {{-h, h, h}, {0,0,1}, {-1,0,0}},
        {{-h, h,-h}, {1,1,0}, {-1,0,0}},

        // Right face (+X)
        {{ h,-h, h}, {1,0,1}, {1,0,0}},
        {{ h,-h,-h}, {0,1,1}, {1,0,0}},
        {{ h, h,-h}, {1,1,1}, {1,0,0}},
        {{ h, h, h}, {0,0,0}, {1,0,0}},

        // Top face (+Y)
        {{-h, h, h}, {1,1,0}, {0,1,0}},
        {{ h, h, h}, {0,1,1}, {0,1,0}},
        {{ h, h,-h}, {1,0,1}, {0,1,0}},
        {{-h, h,-h}, {0,0,1}, {0,1,0}},

        // Bottom face (-Y)
        {{-h,-h,-h}, {1,0,0}, {0,-1,0}},
        {{ h,-h,-h}, {0,1,0}, {0,-1,0}},
        {{ h,-h, h}, {0,0,1}, {0,-1,0}},
        {{-h,-h, h}, {1,1,1}, {0,-1,0}},
    };

    std::vector<uint32_t> idx = {
        // Front
        0,1,2, 2,3,0,
        // Back
        4,5,6, 6,7,4,
        // Left
        8,9,10, 10,11,8,
        // Right
        12,13,14, 14,15,12,
        // Top
        16,17,18, 18,19,16,
        // Bottom
        20,21,22, 22,23,20
    };

    return MeshFilter(verts, idx);
}
