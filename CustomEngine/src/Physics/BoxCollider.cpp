#include "BoxCollider.h"

ColliderDescription BoxCollider::GetColliderDescription() const
{
	return ColliderDescription(ColliderType::Box, m_halfExtends, 0.0f, 0.0f);
}
