#include "Transform.h"

Transform::Transform(glm::vec3 pos) : position(pos){
	
}

Transform::~Transform() {

}

glm::vec3 Transform::GetPosition() {
	return position;
}

const char* Transform::GetComponentName() const {
	return "Transform";
}