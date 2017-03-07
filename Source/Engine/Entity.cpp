#include "Entity.h"

namespace ae
{
	StablePoolArray<Entity> Entity::m_pool;

	int Entity::id()
	{
		return m_id;
	}
}
