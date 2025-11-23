#pragma once

class Component {
protected:
	int componentID;

public:
	Component();
	virtual ~Component();

	virtual const char* GetComponentName() const = 0;
};