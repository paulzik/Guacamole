#pragma once
#include <AL/al.h>
#include "ECS/Component.h"


class AudioListener : public Component {
public:
	void Update() override;
	const char* GetComponentName() const override;
};