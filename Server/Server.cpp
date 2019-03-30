#include "Server.h"

Server::Server()
{

}

bool Server::acceptClient()
{
	if (m_clientsConnected == 0)
	{
		if (m_listener.listen(m_port) != sf::Socket::Done)
		{
			std::cerr << "ERROR: Couldn't bind Listener to port: " << m_port << '\n';
		}

		if (m_listener.accept(m_client1Socket) == sf::Socket::Done)
			std::cout << "Successfully connected client " << ++m_clientsConnected << " (address: " << m_client1Socket.getRemoteAddress() << ")\n";
	}

	else if (m_clientsConnected == 1)
	{
		if (m_listener.listen(m_port) != sf::Socket::Done)
		{
			std::cerr << "ERROR: Couldn't bind Listener to port: " << m_port << '\n';
		}

		if (m_listener.accept(m_client2Socket) == sf::Socket::Done)
			std::cout << "Successfully connected client " << ++m_clientsConnected << '\n';
	}	

	if (m_clientsConnected == 2)
		return true;

	else
		return false;
}

int Server::getClientsConnected() const
{
	return m_clientsConnected;
}

void Server::sendAdresses()
{
	assert(m_clientsConnected == 2 && "more or less than 2 clients are connected");

	sf::IpAddress client1Address{ m_client1Socket.getRemoteAddress() };
	sf::IpAddress client2Address{ m_client2Socket.getRemoteAddress() };

	sf::Packet packet;
	std::string stringClient1{ client1Address.toString() };
	std::string stringClient2{ client2Address.toString() };

	std::cout << "IP address of client 1: " << stringClient1
		<< "\nIP address of client 2: " << stringClient2 << '\n';

	packet << stringClient1;
	m_client1Socket.send(packet);
	packet.clear();

	packet << stringClient2;
	m_client2Socket.send(packet);
	packet.clear();
}

void Server::disconnectClients()
{
	m_client1Socket.disconnect();
	m_client2Socket.disconnect();

	m_clientsConnected = 0;
}