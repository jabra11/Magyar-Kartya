#pragma once

#include "OnlineUser.h"

class Client : public OnlineUser
{
public:
	Client(int port);

	// Returns True if a connection has been established
	bool connect_to_user();

	void receive_deck_information(Deck& copy_to_this, int size_of_deck);

	void set_IP_address(const std::string& address);

private:

	sf::IpAddress m_address_of_other_user;
};

