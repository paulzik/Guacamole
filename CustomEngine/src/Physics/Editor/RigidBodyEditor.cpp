#include "RigidBodyEditor.h"
#include "EditorMacro.h"
#include <imgui_impl_opengl3.h>

void RigidBodyEditor::Draw(Component* component) {
    RigidBody* rb = static_cast<RigidBody*>(component);

    bool mass = rb->mass;
    if (ImGui::Checkbox("Mass", &mass))
    {
        rb->mass = mass;
    }

    bool gravity = rb->useGravity;
    if (ImGui::Checkbox("Use Gravity", &gravity))
    {
        rb->useGravity = gravity;
    }

    bool isKinematic = rb->isKinematic;
    if (ImGui::Checkbox("is Kinematic", &isKinematic))
    {
        rb->isKinematic = isKinematic;
    }
}

CUSTOM_EDITOR(RigidBody, RigidBodyEditor);
