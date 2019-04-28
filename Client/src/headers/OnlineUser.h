#pragma once

#include "Card.h"
#include "Deck.h"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"


class OnlineUser
{
public:

	enum Header
	{
		SETUP_HEADER,
		DEFAULT_HEADER,
		MAX_HEADER,
		PLACE_HOLDER_HEADER
	};

	struct Default_packet
	{
		// check if packet is valid
		bool is_valid{ false };

		// specify the header
		int header{ Header::PLACE_HOLDER_HEADER };

		// User draws a card or uses one.
		bool uses_card{ false };
		int amount_of_cards_drawn{ 0 };

		// Initialize with placeholder values.
		int card_typ{ Card::CardTyp::PLACEHOLDER_TYP };
		int card_rank{ Card::CardRank::PLACEHOLDER_RANK };
		
		// Track the wished card typ if used card happens to be a 7.
		int wishcard_value{ Card::CardTyp::PLACEHOLDER_TYP };
	};

	// Returns a reference to the buffer variable; true returns the player's buffers, false the enemy's
	Default_packet& modify_buffer(bool player = true);

	// Returns a const referenc to the buffer variable
	const Default_packet& get_buffer() const;

	// true flushes the player buffer, false the enemy buffer
	void flush_buffer(bool player);

	// Sends m_buffer to the  
	// connected TCP socket
	void send_choice_information();


	// Retrieves information of a received packet from the established TCP-
	// connection and writes it into m_buffer
	bool receive_choice_information();

protected:

	OnlineUser(int port);

	Default_packet convert_to_Default_packet(const bool is_using_a_card, const Card& card,
		const Card::CardTyp wunsch_typ = Card::CardTyp::PLACEHOLDER_TYP);

	friend sf::Packet& operator<<(sf::Packet& target, const Default_packet& source);
	friend sf::Packet& operator>>(sf::Packet& source, Default_packet& target);


public:
	// a buffer holding information to be send after each turn
	Default_packet m_buffer_player;
	Default_packet m_buffer_enemy;


	int counter{ 0 };

	sf::TcpSocket m_socket;
	int m_port{ 0 };
};