#include "headers/OnlineUser.h"
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

/*bool OnlineUser::request_deck_exchange(Deck& deck)
{
	m_socket.setBlocking(true);

	Default_packet temp;
	temp.is_valid = true;
	temp.header = Header::SETUP_HEADER;
	temp.exchange_deck = true;

	send_choice_information();

	sf::Packet packet;
	packet << temp;
	m_socket.send(packet);



	std::cout << "Requested deck exchange.\nWaiting for answer..\n";
	packet.clear();
	flush_buffer(true);

	if (m_socket.receive(packet) == sf::Socket::Done)
	{
		packet >> temp;

		if (temp.is_valid && temp.header == Header::SETUP_HEADER
			&& temp.exchange_deck)
			std::cout << "Request has been accepted.\n";
	}
	else
	{
		std::cout << "Request has been declined.\n";
		return false;
	}

	if (m_is_host)
		send_deck_information(deck);
	else
		receive_deck_information(deck);

	return true;
	/*
	packet.clear();



	m_socket.receive(packet);

	packet >> temp;

	if (temp.is_valid && temp.header == Header::SETUP_HEADER
		&& temp.exchange_deck)
	{
		std::cout << "Requested deck exchange.\n";
		return true;
	}
	else
		std::cerr << "Request to exchange deck information has failed!\n";
}*/

/*bool OnlineUser::accept_deck_exchange()
{
	m_socket.setBlocking(true);
	
	Default_packet temp;
	temp.is_valid = true;
	temp.header = Header::SETUP_HEADER;
	temp.exchange_deck = true;

	sf::Packet packet;
	packet << temp;

	if (m_socket.send(packet) == sf::Socket::Done)
	{
		std::cout << "Answered request.\n";
		return true;
	}
	else
	{
		std::cout << "Failed to answer request.\n";
		return false;
	}
}*/

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
		//std::cout << "connected to " << m_socket.getRemoteAddress() << std::endl;
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
		/*else if (!card.is_valid && card.header != OnlineUser::Header::SETUP_HEADER)
			assert(false && "ERROR in Client::receive_deck_information()");*/
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