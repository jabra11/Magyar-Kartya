#include <iostream>
#include "SFML/Graphics.hpp"
#include "Card.h"
#include "Deck.h"
#include <array>
#include "textureArray.h"
#include "OnlineEnemy.h"
#include "OnlinePlayer.h"
#include "Logic.h"
#include "Client.h"
#include "Host.h"

int multiplayer(sf::RenderWindow &renderWindow, Logic &logic, const sf::Texture &playTableTexture, const bool bHost)
{
	// load textures
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);

	std::array<sf::Texture, 4> rueckseiten;
	rueckseiten[0].loadFromFile("resources/images/rueckseite/einzel.jpg");
	rueckseiten[1].loadFromFile("resources/images/rueckseite/zwei.png");
	rueckseiten[2].loadFromFile("resources/images/rueckseite/drei.png");
	rueckseiten[3].loadFromFile("resources/images/rueckseite/vier.png");
	sf::Sprite backCard;
	backCard.scale(0.4f, 0.4f);
	backCard.setOrigin(backCard.getGlobalBounds().width, backCard.getGlobalBounds().height);
	backCard.setPosition(1250.0f, 250.0f);

	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");

	Deck deck;
	bool setupFinished{ false };

	// start the setup
	
	// connect to server and get IP address of other user.

	sf::TcpSocket connectToServer;

	while (connectToServer.connect(sf::IpAddress{}.getLocalAddress(), 50000) != sf::Socket::Done)
	{
		std::cerr << "ERROR: Could not connect.\n";
	}

	std::cout << "Connected\n";

	std::string temp;
	sf::Packet myPacket;
	connectToServer.receive(myPacket);
	myPacket >> temp;

	std::cout << "address of other user is : " << temp << '\n';

	// to-do
	// setup client and host game logic. think about how to bring the client and host class into play (as seperate class, friend class or even member variable).
	// 1. establish connection between host and client
	// 2. create game logic





	if (bHost)
	{
		Host host;

	}

	else
	{

	}


	return 0;
}