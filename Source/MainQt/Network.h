#pragma once

#include <QObject.h>
#include <QUdpSocket.h>
#include <functional>

class Network : public QObject
{
	Q_OBJECT

public:
	Network(QObject* parent) : QObject(parent)
	{
		m_socket = new QUdpSocket(this);
		m_socket->bind(QHostAddress::LocalHost, 1234);
		connect(m_socket, &QUdpSocket::readyRead, [=]()
		{
			readyRead();
		});
	}
	void sayHello()
	{
		QByteArray data;
		data.append("Hello from UDP Land");

		m_socket->writeDatagram(data, QHostAddress::LocalHost, 1234);
		//192.168.1.10
		//192.168.1.255

	}

	void readyRead()
	{
		QByteArray buffer;
		buffer.resize(m_socket->pendingDatagramSize());

		QHostAddress sender;
		quint16 senderPort;
		m_socket->readDatagram(buffer.data(), buffer.size(), &sender, &senderPort);

		qDebug() << "Message from: " << sender.toString();
		qDebug() << "Message port: " << senderPort;
		qDebug() << "Message: " << buffer;
	}
protected:

private:
	QUdpSocket* m_socket;
	int id;
};

