#include "AbstractComponent.h"

#include "Entity.h"

namespace ae
{
	int AbstractComponent::idFromEntity(Entity* e)
	{
		return e->id();
	}

}