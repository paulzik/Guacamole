#include <ECS/Scene.h>
#include <Assets/Shader.h>
#include "PickingFramebuffer.h"

class PickingSystem
{
public:
    void Render(Scene& scene);
    EntityID Pick(uint32_t x, uint32_t y);
    void Init(uint32_t width, uint32_t height);

private:
    PickingFramebuffer m_PickingFramebuffer;
    std::shared_ptr<Shader> m_PickingShader;
};
