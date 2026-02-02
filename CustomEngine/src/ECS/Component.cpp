#include "Component.h"

Component::Component() {
    componentID = 0;
    owner = nullptr;
}

void Component::Start() {
    // default empty implementation
}

void Component::Update() {
    // default empty implementation
}

void Component::Destroy() {
    // default empty implementation
}
