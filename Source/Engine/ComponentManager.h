#pragma once
//
//#include "ComponentBase.h"
//#include "ComponentPool.h"
//#include <Utils/Array.h>
//
//
//class ComponentManager
//{
//public:
//	ComponentManager();
//	~ComponentManager();
//
//	template<class T> T* add(int id, const T& value);
//	template<class T> void remove(int id);
//	template<class T> void addType();
//
//	template<class T> T* get(int id);
//
//private:
//	template<class T> int storageIndexFromComponent();
//
//	Array<AbstractComponentPool*> storages;
//};
//
//
//template<class T>
//int ComponentManager::storageIndexFromComponent()
//{
//	int index = ComponentBase<T>::typeId();
//	xassert_msg(index != -1,
//	            "Component must be initialized before use.");
//	return index;
//}
//
//template<class T>
//T* ComponentManager::get(int id)
//{
//	int storageIndex = storageIndexFromComponent<T>();
//	ComponentPool<T>* storage = (ComponentPool<T>*)storages[storageIndex];
//	return storage->valueFromId(id);
//}
//
//template<class T>
//void ComponentManager::remove(int id)
//{
//	int storageIndex = storageIndexFromComponent<T>();
//	ComponentPool<T>* storage = (ComponentPool<T>*)storages[storageIndex];
//	storage->removeAt(id);
//}
//
//template<class T>
//T* ComponentManager::add(int id, const T& value /*= T()*/)
//{
//	// Get type id corresponding to a storage index
//
//	int storageIndex = storageIndexFromComponent<T>();
//
//	// Get storage corresponding to type
//	// and add component
//
//	ComponentPool<T>* storage = (ComponentPool<T>*)storages[storageIndex];
//	int index = storage->add(id, value);
//
//	// Return address to data to allow manipulation
//
//	return &(*storage)[index];
//}
//
//template<class T>
//void ComponentManager::addType()
//{
//	// Make sure T is a component i.e. inherits from Component Type"
//
//	xassert_msg((Util::isOfType<T, ComponentBase<T>>()),
//	            "Only components are allowed.");
//	xassert_msg((ComponentBase<T>::typeId() == -1),
//	            "Component already initialized, please remove duplicate.");
//
//	int id = ComponentBase<T>::typeId();
//	if (id == -1)
//	{
//		// Give type an id
//
//		int id = storages.count();
//		ComponentBase<T>::setTypeId(id);
//
//		// Add new storage
//
//		AbstractComponentPool* storage = new ComponentPool<T>();
//		storages.add(storage);
//	}
//}