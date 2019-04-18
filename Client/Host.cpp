#include "Host.h"



Host::Host(int port)
	:OnlineUser{ port }
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
	

	// disable blocking to allow for smooth gameplay
	m_listener.setBlocking(false);
	m_socket.setBlocking(false);
}

void Host::send_deck_information(Deck& deck_to_send)
{
	for (int i{ 0 }; i < deck_to_send.getSize(); ++i)
	{
		Default_packet card;
		card.card_rank = deck_to_send[i].getRank();
		card.card_typ = deck_to_send[i].getTyp();

		sf::Packet temp;
		temp << card;

		m_socket.send(temp);
	}
}