#include "PickingSystem.h"
#include <GL/glew.h>
#include "ECS/MeshRenderer.h"

void PickingSystem::Render(Scene& scene)
{
    m_PickingFramebuffer.Bind();

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_PickingShader.Bind();

    for (Entity* entity : scene.GetRenderableEntities())
    {
        if (!entity)
            continue;

        if (entity->HasComponent<MeshRenderer>())
        {
            auto& mr = entity->GetComponent<MeshRenderer>();
            mr.Draw(&m_PickingShader, entity->GetID());
        }
    }

    m_PickingFramebuffer.Unbind();
}

EntityID PickingSystem::Pick(uint32_t x, uint32_t y)
{
    m_PickingFramebuffer.Bind();

    EntityID pixel = 0;

    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glReadPixels(
        x, y,
        1, 1,
        GL_RED_INTEGER,
        GL_UNSIGNED_INT,
        &pixel
    );

    m_PickingFramebuffer.Unbind();

    if (pixel != 0)
        ObjectSelection::Set(pixel);
    else
        ObjectSelection::Clear();

    return pixel;
}

