#pragma once

#include "Card.h"
#include "Deck.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

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

	OnlineUser(int port);

	// constructs a Default_packet from the arguments and sends it to the 
	// connected TCP socket
	void send_choice_information(const bool is_using_a_card, const Card& card,
		const Card::CardTyp wunsch_typ = Card::CardTyp::PLACEHOLDER_TYP);


	// retrieves information of a received packet from the established TCP
	// connection and writes it into the first parameter
	void receive_choice_information(OnlineUser::Default_packet& Default_packet_to_write_in,
		const bool is_using_a_card, const Card& card,
		const Card::CardTyp wunsch_typ = Card::CardTyp::PLACEHOLDER_TYP);


	// connects to a given IP address using a TCP socket, meant to be overwritten by 
	// derivatives


	Default_packet convert_to_Default_packet(const bool is_using_a_card, const Card& card,
		const Card::CardTyp wunsch_typ = Card::CardTyp::PLACEHOLDER_TYP);

	friend sf::Packet& operator<<(sf::Packet& target, const Default_packet& source);
	friend sf::Packet& operator>>(sf::Packet& source, Default_packet& target);


protected:

	sf::TcpSocket m_socket;
	int m_port{ 0 };
};