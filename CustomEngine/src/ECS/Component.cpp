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
