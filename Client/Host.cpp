#include "Host.h"



Host::Host(int port)
	:OnlineUser{ port }
{
}

bool Host::wait_for_connection(int port)
{
	if (m_listener.listen(port) == sf::Socket::Done)
	{
		std::cout << "Listening to port " << port << ".\n";

		if (m_listener.accept(m_socket) == sf::Socket::Done)
		{
			std::cout << "Successfully connected: " << m_socket.getRemoteAddress() << ".\n";
			return true;
		}

		else
		{
			std::cerr << "Couldn't establish any connections on port " << port << ".\n";
			return false;
		}
	}

	else
	{
		std::cerr << "Couldn't listen to port " << port << ".\n";
		return false;
	}
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