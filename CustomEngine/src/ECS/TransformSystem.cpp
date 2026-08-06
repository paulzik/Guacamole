#include "TransformSystem.h"
#include "Scene.h"

bool TransformSystem::Init()
{
	return true;
}

void TransformSystem::Update()
{
    for (const auto& e : Scene::Get().GetEntities())
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

}
