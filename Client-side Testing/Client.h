#pragma once
#pragma once

#include "SFML/Network.hpp"
#include "User.h"

class Client : public User
{
private:
	std::vector<CardInfo> m_copyOfTheDeck;

public:
	Client(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> *pointerToDeck = nullptr,
		std::vector<CardInfo> *pointerToHand = nullptr);

	void receiveDeckInfo();

	
};