//#pragma once
//
//#include "AbstractComponentPool.h"
//#include <Utils/PoolArray.h>
//#include <Utils/Math.h>
//
//class Entity;
//
//template<class T>
//class ComponentPool : public AbstractComponentPool
//{
//public:
//	void clear()
//	{
//		PoolArray::clear();
//		m_indices.clear();
//	}
//
//	int add(int id, const T& value)
//	{
//		// Reuse previous index or allocate a new one
//		int index = indexFromId(id);
//		if (index = -1)
//		{
//			index = m_firstGap;
//
//			// Increase capacity if necessary
//			if (index == m_values.count())
//			{
//				m_values.addEmpty();
//				m_gaps.addEmpty();
//				m_enabled.addEmpty();
//				m_ids.addEmpty();
//			}
//		}
//		
//		m_values[index] = value;
//		m_gaps[index] = false;
//		m_enabled[index] = true;
//		m_ids[index] = id;
//		m_count++;
//
//		// Save id to be able to retrieve values later
//		while (id >= m_indices.count())
//			m_indices.add(-1);
//		m_indices[id] = index;
//
//		findNextGap();
//
//		return index;
//	}
//	int index(const T& value)
//	{
//		return static_cast<int>(&m_values[0] - &value);
//	}
//	int id(const T& value)
//	{
//		return  idFromIndex(index(value));
//	}
//
//	void removeAt(int id)
//	{
//		int index = indexFromId(id);
//		if (index != -1)
//		{
//			// Remove value
//
//			m_gaps[index] = true;
//			m_enabled[index] = false;
//			m_ids[id] = -1;
//			m_count--;
//
//			// Check if new first gap is needed
//
//			if (index < m_firstGap)
//				m_firstGap = index;
//
//			// If value was next to last gap a new gap is needed
//
//			if (index == m_lastGap - 1)
//			{
//				findNextLastGap();
//			}
//		}
//	}
//
//	T* valueFromId(int id)
//	{
//		/*int index = indexFromId(id);
//		if (index != -1)
//			return &(*this)[index];*/
//
//		return nullptr;
//	}
//
//	/// Returns the index belonging to an id, returns "-1" if no index exists.
//	int indexFromId(int id)
//	{
//		if (id < m_indices.count())
//			return m_indices[id];
//		return -1;
//	}
//	/// Returns id belonging to index, id typically represents owner of value stored at index.
//	int idFromIndex(int index)
//	{
//		return m_ids[index];
//	}
//
//public:
//	bool isEnabled(int index) const
//	{
//		return m_enabled[index];
//	}
//
//	Array<bool> m_enabled;
//	Array<int> m_ids;
//	Array<int> m_indices;
//	PoolArray<T> m_pool;
//
//	#pragma region Iterator
//public:
//	class Iterator
//	{
//	public:
//		Iterator(ComponentPool* target, int index)
//		{
//			m_target = target;
//			m_index = index;
//			ignoreDisabled();
//		}
//		void reset()
//		{
//			m_index = 0;
//		}
//		bool operator!=(const Iterator& other) const
//		{
//			return m_index < other.m_index;
//		}
//		T* operator*()
//		{
//			return &m_target->m_values[m_index];
//		}
//		const T* operator*() const
//		{
//			return &m_target->m_values[m_index];
//		}
//		int id() const
//		{
//			return m_target->idFromIndex(m_index);
//		}
//
//		const Iterator& operator++()
//		{
//			m_index++;
//			ignoreDisabled();
//
//			return *this;
//		}
//
//	private:
//		void ignoreDisabled()
//		{
//			while (m_index < m_target->m_lastGap && !m_target->isEnabled(m_index))
//			{
//				m_index++;
//			}
//		}
//
//		int m_index;
//		ComponentPool* m_target;
//	};
//	Iterator begin()
//	{
//		return Iterator(this, 0);
//	}
//	Iterator end()
//	{
//		return Iterator(this, m_lastGap);
//	}
//	#pragma endregion
//};