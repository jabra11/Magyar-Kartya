#pragma once

#include "OnlineUser.h"

class Client : public OnlineUser
{
public:
	Client(int port);

	// Returns True if a connection has been established
	bool connect_to_user(sf::IpAddress& ip_address);

	void receive_deck_information(Deck& copy_to_this, int size_of_deck);

private:

	sf::IpAddress m_address_of_other_user;
};

