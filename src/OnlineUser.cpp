#include "OnlineUser.hpp"
#include <cassert>
#include <utility>

OnlineUser::OnlineUser(unsigned short port, bool is_host)
	:m_port{port}, m_is_host{is_host}
{
	m_socket.setBlocking(true);
}


sf::Packet& operator<<(sf::Packet &packet, const OnlineUser::Default_packet &card)
{
	return packet << card.is_valid << card.header << card.exchange_deck << card.uses_card << card.amount_of_cards_drawn << card.card_rank << card.card_typ << card.wishcard_value;
}


sf::Packet& operator>>(sf::Packet &packet, OnlineUser::Default_packet &card)
{
	return packet >> card.is_valid >> card.header >> card.exchange_deck >> card.uses_card >> card.amount_of_cards_drawn >> card.card_rank >> card.card_typ >> card.wishcard_value;
}


void OnlineUser::send_choice_information()
{
	// block socket to safely send informations
	m_socket.setBlocking(true);

	sf::Packet temp;

	m_buffer_player.header = Header::DEFAULT_HEADER;

	temp << m_buffer_player;

	if (m_buffer_player.is_valid)
		std::cout << "packet is valid\n";
	else
		std::cout << "packet isn't valid\n";

	std::cout << "Sending packet..\n";
	if (m_socket.send(temp) == sf::Socket::Done)
		std::cout << "Successfully sent packet. # " << ++counter << "\n";

	else
	{
		std::cerr << "ERROR: Couldn't send the packet.\n";
		m_socket.disconnect();
	}

	flush_buffer(true);

	// unblock socket to allow for smooth gameplay
	m_socket.setBlocking(false);
}


const sf::Socket::Status OnlineUser::receive_choice_information()
{
	sf::Packet temp;
	bool received_a_packet{ false };

	m_socket.setBlocking(true);

	std::cout << "Waiting for a packet .. \n";

	if (m_socket.receive(temp) == sf::Socket::Done)
	{
		std::cout << "Validating packet ..\n";
		received_a_packet = true;
	}
	else
	{
		std::cerr << "ERROR: Did not receive any packet.\n";
		m_socket.disconnect();

		return sf::Socket::Disconnected;
	}

	if (received_a_packet)
	{
		Default_packet tempP;
		temp >> tempP;

		if (tempP.is_valid && tempP.header == Header::DEFAULT_HEADER)
		{
			m_buffer_enemy = tempP;
			std::cout << "Validated packet.\n";
			return sf::Socket::Done;
		}
		else
		{
			std::cout << "contents of packet\nvalid:" << tempP.is_valid << "\nheader:" << tempP.header
				<< "\nexchange deck:" << tempP.exchange_deck << std::endl;

			std::cerr << "ERROR: Packet is invalid!\n";
			return sf::Socket::Error;
		}
	}
}

OnlineUser::Default_packet& OnlineUser::modify_buffer(bool player)
{
	if (player)
		return m_buffer_player;
	else
		return m_buffer_enemy;
}

const OnlineUser::Default_packet& OnlineUser::get_buffer() const
{
	return m_buffer_player;
}

void OnlineUser::flush_buffer(bool player)
{
	if (player)
		m_buffer_player = OnlineUser::Default_packet{};
	else
		m_buffer_enemy = OnlineUser::Default_packet{};
}

void OnlineUser::receive_deck_information(Deck& deck_to_copy_in)
{
	m_socket.setBlocking(true);

	std::cout << "syncing deck now..\n";

	int counter{ 0 };


	for (int i{ 0 }; true;)
	{
		sf::Packet temp;
		m_socket.receive(temp);
		Default_packet card;
		temp >> card;

		if (card.is_valid && card.header == OnlineUser::Header::SETUP_HEADER)
		{
			std::cout << "received #" << i << std::endl;

			deck_to_copy_in[i].setRank(static_cast<Card::CardRank>(card.card_rank));
			deck_to_copy_in[i].setTyp(static_cast<Card::CardTyp>(card.card_typ));
			deck_to_copy_in[i].setTexture();
			++i;
		}
		else if (!card.is_valid && card.header == OnlineUser::Header::SETUP_HEADER)
		{
			std::cout << "received terminator\n";
			counter = i;
			break;
		}
	}

	std::cout << "Deck is syncronized. Received " << counter << " Cards.\n";
	m_socket.setBlocking(false);
}

void OnlineUser::send_deck_information(Deck& deck_to_send)
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
}