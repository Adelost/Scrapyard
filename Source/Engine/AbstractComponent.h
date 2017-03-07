#pragma once

#include <Utils/Inspectable.h>

namespace ae
{
	class Entity;

	/// Allows access to logic shared with all components.
	class AbstractComponent
	{
	public:
		/// Sets up a dependency to another component belonging to the same
		///	entity and allows access to it.
		///	
		///	Should be used as a member inside a component and be initialized in
		///	the constructor. Upon initialization it will create a direct link to
		///	the other component. Lookup is based on entity id and the entity
		///	must already have the underlying component.
		template<class T>
		class Dependency
		{
		public:
			Dependency(int id)
			{
				// Fetch component or create if not exists.
				m_ptr = T::Create(id);
				
				/*xassert_msg(m_ptr != nullptr, "A Component required by another Component is missing from the shared Entity. Check your Entity and make sure all component dependencies are satisfied.");*/
			}

			T* get()
			{
				return m_ptr;
			}

			T* operator->()
			{
				return get();
			}

		private:
			T* m_ptr;
		};

	public:
		AbstractComponent(int id)
		{
			m_id = id;
		}

	protected:
		static int idFromEntity(Entity* e);
	
	private:
		int m_id;
	};
}