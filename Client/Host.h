#pragma once

#include "OnlineUser.h"

class Host : public OnlineUser
{
public:

	Host(int port);

	// Returns True if a connection has been established
	bool wait_for_connection(int port);

	void send_deck_information(Deck& deck_to_send);

private:

	sf::TcpListener m_listener;
};

