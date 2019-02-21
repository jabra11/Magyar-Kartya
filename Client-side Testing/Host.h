#pragma once
#include "User.h"

class Host : public User
{
public:
	Host(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> *pointerToDeck = nullptr, 
		std::vector<CardInfo> *pointerToHand = nullptr);

	void sendDeckInfo();
};

