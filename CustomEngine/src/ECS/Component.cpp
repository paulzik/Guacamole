#include "Component.h"

Component::Component() {
    componentID = 0;
    owner = nullptr;
}

Component::~Component() {

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

void Component::setOwner(Entity* _owner)
{
    owner = _owner;
}

Entity* Component::getOwner()
{
    return owner;
}
