#pragma once

#include "Card.hpp"
#include "Deck.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"

// class forward declaration to avoid circular dependency issue.. 
class Deck;

class OnlineUser
{
public:

	// Enumerator containing Header statuses
	enum Header
	{
		SETUP_HEADER,
		DEFAULT_HEADER,
		MAX_HEADER,
		INVALID_HEADER
	};


	// Structure of the packet
	struct Default_packet
	{
		// check if packet is valid
		bool is_valid{ false };

		// specify the header
		int header{ Header::INVALID_HEADER };
		bool exchange_deck{false};

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

	// Sends m_buffer to the connected TCP socket
	void send_choice_information();


	// Retrieves information of a received packet from the established TCP-
	// connection and writes it into m_buffer
	const sf::Socket::Status receive_choice_information();

	// Sends the deck in the parameter to the connected TCP-Socket.
	void send_deck_information(Deck& send_this);

	// Writes from the connected TCP-Socket received information to the parameter
	void receive_deck_information(Deck& write_to_this);



protected:

	OnlineUser(unsigned short port, bool is_host);

	friend sf::Packet& operator<<(sf::Packet& write_in, const Default_packet& write_from);
	friend sf::Packet& operator>>(sf::Packet& write_from, Default_packet& write_in);


public:
	// buffers holding information to be send after each turn
	Default_packet m_buffer_player;
	Default_packet m_buffer_enemy;


	int counter{ 0 };

	sf::TcpSocket m_socket;
	unsigned short m_port{ 0 };

private:
	bool m_is_host{ false };
};