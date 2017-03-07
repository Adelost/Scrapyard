#include "Message.h"
//
//#include "MessageSystem.h"
//
//Message::Message(std::string type)
//{
//	m_type = type;
//	m_accepted = false;
//	m_byteIndex = messageSystem.byteIndex();
//}
//
//template<class T>
//void Message::add(const T& value)
//{
//	messageSystem.add(value);
//}
//
//template<class T>
//Message& Message::operator<<(const T& value)
//{
//	messageSystem.add(value);
//	return *this;
//}
//
//template<class T>
//T Message::get()
//{
//	return messageSystem.get<T>();
//}
//
//void Message::send()
//{
//	messageSystem.send(this, m_type);
//}
//
//void Message::accept()
//{
//	m_accepted = true;
//}
//
//bool Message::accepted()
//{
//	return m_accepted;
//}
//
//int Message::byteIndex()
//{
//	return m_byteIndex;
//}
