#include "Systems/System.h"
#include <Assets/Shader.h>

class GizmoRendererSystem : public System
{
public:
    bool Init() override;
    void Update() override;
    void Shutdown() override;

private:
    unsigned int vao;
    unsigned int vbo;
    Shader* gizmoShader;
};
