#pragma once

#include "OnlineUser.hpp"

class Client : public OnlineUser
{
public:
	Client(unsigned short port, bool is_host);

	// Returns True if a connection has been established
	bool connect_to_user();


	void set_IP_address(const std::string& address);


private:

	sf::IpAddress m_address_of_other_user;
};

