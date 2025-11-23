#pragma once
#include "ECS/MeshFilter.h"


class PrimitiveFactory {
protected:


public:
	PrimitiveFactory();
	virtual ~PrimitiveFactory();

	static MeshFilter CreateCubePrimitive(float size = 1.0f);
	//static MeshFilter CreatePlanePrimitive(float size = 1.0f);
	//static MeshFilter CreateSpherePrimitive(float size = 1.0f);
};