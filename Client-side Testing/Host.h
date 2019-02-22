#pragma once
#include "User.h"

class Host : public User
{
	sf::TcpListener m_myListener;
public:
	Host(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> &pointerToDeck, 
		std::vector<CardInfo> &pointerToHand);

	void sendDeckInfo();

	void connectToOtherGuy() override;
};

