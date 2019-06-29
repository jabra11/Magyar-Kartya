#include "headers/Host.hpp"



Host::Host(unsigned short port, bool is_host)
	:OnlineUser{ port, is_host }
{
	m_listener.setBlocking(false);
}

bool Host::wait_for_connection(bool* done)
{
	// enable blocking to safely establish a connection.
	m_listener.setBlocking(true);
	m_socket.setBlocking(true);

	
	if (m_listener.listen(m_port) == sf::Socket::Done)
	{
		std::cout << "Listening to port " << m_port << ".\n";

		if (m_listener.accept(m_socket) == sf::Socket::Done)
		{
			std::cout << "Successfully connected: " << m_socket.getRemoteAddress() << ".\n";
			std::cout << m_socket.getRemoteAddress() << " uses port: " << m_socket.getRemotePort() << ".\n";
			*done = true;
			return true;
		}

		else
		{
			std::cerr << "Couldn't establish any connections on port " << m_port << ".\n";
			*done = false;
			return false;
		}
	}

	else
	{
		std::cerr << "Couldn't listen to port " << m_port << ".\n";
		*done = false;
		return false;
	}
}