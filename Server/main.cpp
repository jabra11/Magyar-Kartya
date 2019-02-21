#include <iostream>
#include <SFML/Network.hpp>
#include "Server.h"

int main()
{
	Server server;

	while (server.getClientsConnected() != 2)
	{
		server.acceptClient();
	}
	server.sendAdresses();
}