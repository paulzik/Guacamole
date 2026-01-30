#include "TransformSystem.h"
#include "Scene.h"

bool TransformSystem::Init()
{
	return false;
}

void TransformSystem::Update()
{
    const auto& entities = Scene::Get().GetEntities();

    for (Entity* e : entities)
    {
        Transform* t = e->TryGetComponent<Transform>();
        if (!t) continue;

        glm::mat4 m(1.0f);
        m = glm::translate(m, t->position);
        m *= glm::mat4_cast(t->rotation);
        m = glm::scale(m, t->scale);

        t->modelMatrix = m;
    }
}


void TransformSystem::Shutdown()
{
	transforms.clear();
}
