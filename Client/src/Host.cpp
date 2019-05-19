#include "headers/Host.h"



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

/*void Host::send_deck_information(Deck& deck_to_send)
{
	m_socket.setBlocking(true);
	int counter{ 0 };
	for (int i{ 0 }; i < deck_to_send.getSize() + 1; ++i)
	{
		if (i < deck_to_send.getSize())
		{
			std::cout << "sending card..\n";
			++counter;
			Default_packet card;
			card.is_valid = true;
			card.header = OnlineUser::Header::SETUP_HEADER;
			card.card_rank = deck_to_send[i].getRank();
			card.card_typ = deck_to_send[i].getTyp();

			sf::Packet temp;
			temp << card;

			m_socket.send(temp);
		}
		else if (i == deck_to_send.getSize())
		{
			std::cout << "sending terminator..\n";
			Default_packet card;
			card.is_valid = false;
			card.header = OnlineUser::Header::SETUP_HEADER;

			sf::Packet temp;
			temp << card;
			m_socket.send(temp);
		}
	}

	std::cout << "Sent deck informations containing	" << counter << " cards.\n";
	m_socket.setBlocking(false);
}*/