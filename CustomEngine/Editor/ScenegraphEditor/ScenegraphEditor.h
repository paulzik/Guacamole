#pragma once
#include <vector>
#include <ECS/Entity.h>
#include "EditorWindow.h"
#include "Scenegraph/Scenegraph.h"

class ScenegraphEditor : public EditorWindow {
private:
	Scenegraph* scenegraph;

public:
	ScenegraphEditor(Scenegraph* _scenegraph);
	~ScenegraphEditor();
	virtual void Draw();
};