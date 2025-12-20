#include "PickingSystem.h"
#include <GL/glew.h>

void PickingSystem::Render(Scene& scene)
{
    m_PickingFramebuffer.Bind();
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_PickingShader.Bind();

    for (auto entity : scene.GetRenderableEntities())
    {
        m_PickingShader.SetUInt("u_EntityID", entity.GetID());
        entity.GetMesh().Draw();
    }

    m_PickingFramebuffer.Unbind();
}
