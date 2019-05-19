#include "headers/Client.h"
#include <cassert>


Client::Client(unsigned short port, bool is_host)
	:OnlineUser{port, is_host}
{
	m_address_of_other_user = sf::IpAddress::None;
}

bool Client::connect_to_user()
{
	// enable blocking to safely establish a connection
	m_socket.setBlocking(true);
	if (m_socket.connect(m_address_of_other_user, m_port, sf::Time(sf::seconds(3.0f))) == sf::Socket::Done)
	{
		std::cout << "Successfully connected to " << m_address_of_other_user << " on port " << m_socket.getRemotePort() << ".\n";
		return true;
	}

	else
	{
		std::cerr << "Couldn't connect to " << m_address_of_other_user << ".\n";
		return false;
	}
}

void Client::set_IP_address(const std::string& address)
{
	sf::IpAddress temp { address };
	m_address_of_other_user = temp;
	std::cout << "IP-address of other user is now: " << address << '\n';
}
