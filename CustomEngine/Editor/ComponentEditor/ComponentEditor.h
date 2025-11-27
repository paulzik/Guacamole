#pragma once
#include <vector>
#include "ECS/Component.h"

class ComponentEditor {
protected:

public:
	virtual ~ComponentEditor() = default;
	virtual void Draw(Component* component) = 0;
};