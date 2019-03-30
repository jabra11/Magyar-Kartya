#pragma once

#include "SFML/Network.hpp"
#include "User.h"
#include <iostream>

class Client : public User
{
private:
	std::vector<CardInfo> m_copyOfTheDeck;

public:
	Client(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> &pointerToDeck,
		std::vector<CardInfo> &pointerToHand);

	void receiveDeckInfo();

	void printDeck();
};