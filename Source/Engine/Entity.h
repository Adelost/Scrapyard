#pragma once

#include <Utils/StablePoolArray.h>

namespace ae
{
	/// Standard representation of a game entity.
	class Entity
	{
	public:
		/// Add component.
		template<class T>
		void addComponent(const T& component)
		{
		}

		/// Remove component.
		template<class T>
		void removeComponent()
		{
		}

		/// Get component.
		template<class T> T* component();			
		int id();

		static Entity* Create()
		{
			int index = m_pool.add(Entity());
			Entity* e = &m_pool[index];
			e->m_id = index;

			return e;
		}

	private:
		Entity()
		{
		}

		int m_id;
		static ae::StablePoolArray<Entity> m_pool;
	};
}