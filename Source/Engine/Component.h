#pragma once

#include <Engine/AbstractComponent.h>
#include <Utils/IdPoolArray.h>
#include <assert.h>

namespace ae
{
	/// Template class all components should inherit from. It is used to manage
	///	class specific logic shared with all component such as generating a unique
	///	class id used to identify a component.
	template<class T>
	class Component : public AbstractComponent
	{
	public:
		Component(int id) : AbstractComponent(id) {}

		static T* Create(Entity* entity)
		{
			return Create(idFromEntity(entity));
		}

		static T* Create(int id)
		{
			return s_pool.add(id, T(id));
		}

		static T* Get(Entity* entity)
		{
			return Get(idFromEntity(entity));
		}

		static T* Get(int id)
		{
			return s_pool.valueFromId(id);
		}

		int entityId()
		{
			T* component = static_cast<T*>(this);
			return s_pool.id(*component);
		}

		#pragma region Iterator
	public:
		class ComponentIterator
		{
		public:
			typename IdPoolArray<T>::Iterator begin()
			{
				return s_pool.begin();
			}
			typename IdPoolArray<T>::Iterator end()
			{
				return s_pool.end();
			}
		};

		static ComponentIterator Iterator()
		{
			return s_iterator;
		}
		#pragma endregion

	private:
		static int s_typeId;
		static IdPoolArray<T> s_pool;
		static ComponentIterator s_iterator;
	};

	template<class T>
	typename Component<T>::ComponentIterator Component<T>::s_iterator;

	template<class T>
	IdPoolArray<T> Component<T>::s_pool;
}