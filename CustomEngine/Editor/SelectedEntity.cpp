#include "SelectedEntity.h"

Entity* SelectedEntity::selected = nullptr;

void SelectedEntity::Set(Entity* se) {
	selected = se;
}

Entity* SelectedEntity::Get() {
	return selected;
}

