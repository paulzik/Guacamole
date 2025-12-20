#include <ECS/Scene.h>
#include <Assets/Shader.h>
#include "PickingFramebuffer.h"

class PickingSystem
{
public:
    void Render(Scene& scene);
    EntityID Pick(uint32_t x, uint32_t y);

private:
    PickingFramebuffer m_PickingFramebuffer;
    Shader m_PickingShader;
};
