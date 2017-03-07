#pragma once

#include <string>

class Message
{
public:
	Message(std::string type);

	template<class T>
	void add(const T& value);

	template<class T> Message& operator<<(const T& value);
	template<class T> T get();
	void send();
	/// The message will not be sent to subsequent subscribers
	void accept();
	/// Returns true if the message has been accepted by someone
	bool accepted();
	int byteIndex();

private:
	std::string  m_type;
	bool m_accepted;
	int m_byteIndex;
};
