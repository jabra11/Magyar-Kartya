#include "Client.h"



Client::Client(int port)
	:OnlineUser{port}
{
}

bool Client::connect_to_user(sf::IpAddress& ip_address)
{
	if (m_socket.connect(ip_address, m_port) == sf::Socket::Done)
	{
		std::cout << "Successfully connected to " << ip_address.getPublicAddress();
		return true;
	}

	else
	{
		std::cerr << "Couldn't connect to " << ip_address.getPublicAddress();
		return false;
	}
}

void Client::receive_deck_information(Deck& deck_to_copy_in, int size_of_deck)
{
	for (int i{ 0 }; i < size_of_deck; ++i)
	{
		sf::Packet temp;
		m_socket.receive(temp);

		Default_packet card;
		
		temp >> card;
		
		deck_to_copy_in[i].setRank(static_cast<Card::CardRank>(card.card_rank));
		deck_to_copy_in[i].setTyp(static_cast<Card::CardTyp>(card.card_typ));
	}
}