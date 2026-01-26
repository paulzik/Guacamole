#pragma once
#include "ECS/Component.h"

class Collider : public Component{
public:
	Collider(bool trigger) :isTrigger(trigger) {};
	bool isTrigger;
	void Start() override;
	void Update() override;

	const char* GetComponentName() const override;
private:

};