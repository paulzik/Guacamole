#pragma once
#include <vector>

class EditorWindow {
protected:
	const char* windowName;

public:
	EditorWindow(const char* name);
	~EditorWindow();
	virtual void Draw() = 0;
};