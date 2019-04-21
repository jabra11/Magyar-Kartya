#pragma once

#include "OnlineUser.h"


class Host : public OnlineUser
{

public:

	Host(int port);

	// Returns True if a connection has been established.
	bool wait_for_connection(bool* done);

	// Sends the deck in the parameter to the connected TCP-Socket.
	void send_deck_information(Deck& deck_to_send);


	// data members


	// has a thread been enlisted to establish a connection
	bool m_enlisted_thread{ false };


	// has a connection been established?
	bool m_found_a_connection{ false };

private:

	sf::TcpListener m_listener;
};

