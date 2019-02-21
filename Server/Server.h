#ifndef SERVER_H
#define SERVER_H


#include <string>
#include <SFML/Network.hpp>
#include <array>
#include <iostream>
#include <cassert>

class Server
{
private:
	sf::TcpListener m_listener;

	sf::TcpSocket m_client1Socket;
	sf::TcpSocket m_client2Socket;

	int m_clientsConnected{ 0 };
	int m_port{ 50000 };

public:

	Server();

	int getClientsConnected() const;

	bool acceptClient();

	void sendAdresses();
};

#endif