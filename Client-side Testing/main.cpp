#include <iostream>
#include <string>
#include <thread>

#include "SFML/Network.hpp"
#include "Host.h"
#include "Client.h"


int main()
{
	int port{ 55000 };
	/*std::cout << "enter port: ";
	std::cin >> port;*/

	sf::TcpSocket mySocket;

	while (mySocket.connect(sf::IpAddress{}.getLocalAddress(), 50000) != sf::Socket::Done)
	{
		std::cerr << "ERROR: Could not connect.\n";
	}

	std::cout << "Connected\n";

	std::string temp;
	sf::Packet myPacket;
	mySocket.receive(myPacket);
	myPacket >> temp;

	std::cout << "1.host or 2.client?\n";
	int decision;
	std::cin >> decision;


	std::vector<User::CardInfo> testDeck;
	testDeck.resize(32);


	if (decision == 1)
	{
		for (int i{ 0 }; i < 32; ++i)
			testDeck[i] = User::CardInfo{ 1, 2, 5 };

		Host host{ temp, testDeck, testDeck};
		
		host.connectToOtherGuy();
		//system("pause");
		host.sendDeckInfo();
	}

	else if (decision == 2)
	{
		Client client{ temp, testDeck, testDeck };

		client.connectToOtherGuy();
		//system("pause");
		client.receiveDeckInfo();
		client.printDeck();
	}

	system("pause");
}