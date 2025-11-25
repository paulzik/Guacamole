#include "PrimitiveFactory.h"
#include <glm/geometric.hpp>

PrimitiveFactory::PrimitiveFactory() {

}

PrimitiveFactory::~PrimitiveFactory() {

}

MeshFilter PrimitiveFactory::CreateCubePrimitive(float size)
{
    float h = size * 0.5f;

    std::vector<Vertex> verts = {
        // ---------- FRONT (+Z) ----------
        {{-h,-h, h}, {1,0,0}, {0,0,1}},   
        {{ h,-h, h}, {0,1,0}, {0,0,1}},   
        {{ h, h, h}, {0,0,1}, {0,0,1}},   
        {{-h, h, h}, {1,1,0}, {0,0,1}},   

        // ---------- BACK (-Z) ----------
        {{ h,-h,-h}, {1,0,1}, {0,0,-1}},  
        {{-h,-h,-h}, {0,1,1}, {0,0,-1}},  
        {{-h, h,-h}, {1,1,1}, {0,0,-1}},  
        {{ h, h,-h}, {0,0,0}, {0,0,-1}},  

        // ---------- LEFT (-X) ----------
        {{-h,-h,-h}, {1,0,0}, {-1,0,0}},  
        {{-h,-h, h}, {0,1,0}, {-1,0,0}},  
        {{-h, h, h}, {0,0,1}, {-1,0,0}},  
        {{-h, h,-h}, {1,1,0}, {-1,0,0}},  

        // ---------- RIGHT (+X) ---------
        {{ h,-h, h}, {1,0,1}, {1,0,0}},   
        {{ h,-h,-h}, {0,1,1}, {1,0,0}},   
        {{ h, h,-h}, {1,1,1}, {1,0,0}},   
        {{ h, h, h}, {0,0,0}, {1,0,0}},   

        // ---------- TOP (+Y) ----------
        {{-h, h, h}, {1,1,0}, {0,1,0}},   
        {{ h, h, h}, {0,1,1}, {0,1,0}},   
        {{ h, h,-h}, {1,0,1}, {0,1,0}},   
        {{-h, h,-h}, {0,0,1}, {0,1,0}},   

        // ---------- BOTTOM (-Y) --------
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

MeshFilter PrimitiveFactory::CreateSpherePrimitive(float radius)
{
    const int sectors = 32; // longitude
    const int stacks = 16;  // latitude

    std::vector<Vertex> verts;
    std::vector<uint32_t> idx;

    const float PI = 3.14159265359f;

    for (int i = 0; i <= stacks; ++i)
    {
        float stackPerc = (float)i / stacks;
        float phi = PI * (stackPerc - 0.5f); // -PI/2 → +PI/2

        for (int j = 0; j <= sectors; ++j)
        {
            float sectorPerc = (float)j / sectors;
            float theta = sectorPerc * 2.0f * PI; // 0 → 2PI

            // Position on sphere
            float x = radius * cos(phi) * cos(theta);
            float y = radius * sin(phi);
            float z = radius * cos(phi) * sin(theta);

            glm::vec3 pos(x, y, z);
            glm::vec3 normal = glm::normalize(pos);
            glm::vec3 color = { sectorPerc, stackPerc, 1.0f - sectorPerc }; // debug color

            verts.push_back({ pos, color, normal });
        }
    }

    // Indices
    for (int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for (int j = 0; j < sectors; ++j)
        {
            // Quad → two triangles
            idx.push_back(k1 + j);
            idx.push_back(k2 + j);
            idx.push_back(k1 + j + 1);

            idx.push_back(k1 + j + 1);
            idx.push_back(k2 + j);
            idx.push_back(k2 + j + 1);
        }
    }

    return MeshFilter(verts, idx);
}

