#include "AudioListener.h"
#include "ECS/Transform.h"
#include "ECS/TransformUtils.h"
#include "ECS/Entity.h"

void AudioListener::Update()
{
    if (!owner)
        return;

    Transform& transform = owner->GetComponent<Transform>();

    // Position
    glm::vec3 pos = transform.position;
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);

    // Orientation (forward + up)
    glm::vec3 forward = GetForward(transform);
    glm::vec3 up = transform.up;

    float orientation[6] = {
        forward.x, forward.y, forward.z,
        up.x,      up.y,      up.z
    };

    alListenerfv(AL_ORIENTATION, orientation);
}

const char* AudioListener::GetComponentName() const
{
    return "AudioListener";
}
