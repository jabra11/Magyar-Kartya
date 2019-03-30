#pragma once

#include "Card.h"
#include "Deck.h"
#include "SFML/Network.hpp"

class OnlineUser
{
public:

	struct Default_packet
	{
		// User draws a card or uses one.
		bool uses_card{ false };

		// Initialize with placeholder values.
		int card_typ{ Card::CardTyp::PLACEHOLDER_TYP };
		int card_rank{ Card::CardRank::PLACEHOLDER_RANK };

		// Track the wished card typ if used card happens to be a 7.
		int wunschkarte_value{ Card::CardTyp::PLACEHOLDER_TYP };

	};

protected:

	OnlineUser();


	void send_card_information(const Default_packet& packet_to_send);
	void receive_card_information(Default_packet& packet_to_receive);

	virtual void connect_to_user(sf::IpAddress& target_address) = 0;

	sf::TcpSocket m_my_socket;
	sf::IpAddress address_of_other_user;

	friend sf::Packet& operator<<(sf::Packet& target, const Default_packet& source);
	friend sf::Packet& operator>>(sf::Packet& source, const Default_packet& target);
};

