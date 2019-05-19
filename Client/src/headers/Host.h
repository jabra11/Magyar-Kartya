#pragma once

#include "OnlineUser.h"

class Host : public OnlineUser
{

public:

	Host(unsigned short port, bool is_host);

	// Returns True if a connection has been established.
	bool wait_for_connection(bool* done);

	// has a thread been enlisted to establish a connection
	bool m_enlisted_thread{ false };


	// has a connection been established?
	bool m_found_a_connection{ false };

private:

	sf::TcpListener m_listener;
};

