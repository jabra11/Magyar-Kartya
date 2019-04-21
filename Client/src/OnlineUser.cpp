#include "headers/OnlineUser.h"

OnlineUser::OnlineUser(int port)
	:m_port{port}
{
	m_socket.setBlocking(true);
}


sf::Packet& operator<<(sf::Packet &packet, const OnlineUser::Default_packet &card)
{
	return packet << card.is_valid << card.uses_card << card.amount_of_cards_drawn << card.card_rank << card.card_typ << card.wishcard_value;
}


sf::Packet& operator>>(sf::Packet &packet, OnlineUser::Default_packet &card)
{
	return packet >> card.is_valid >> card.uses_card >> card.amount_of_cards_drawn >> card.card_rank >> card.card_typ >> card.wishcard_value;
}


void OnlineUser::send_choice_information()
{
	// block socket to safely send informations
	m_socket.setBlocking(true);

	sf::Packet temp;

	temp << m_buffer_player;

	if (m_buffer_player.is_valid)
		std::cout << "packet is valid\n";
	else
		std::cout << "packet isnt valid\n";

	std::cout << "Sending packet..\n";
	if (m_socket.send(temp) == sf::Socket::Done)
		std::cout << "Successfully sent packet. # " << ++counter << "\n";

	else
		std::cerr << "ERROR: Couldn't send the packet.\n";

	flush_buffer(true);

	// unblock socket to allow for smooth gameplay
	m_socket.setBlocking(false);
}


bool OnlineUser::receive_choice_information()
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
		std::cerr << "ERROR: Did not receive any packet.\n";

	m_socket.setBlocking(true);

	if (received_a_packet)
	{
		OnlineUser::Default_packet tempP;
		temp >> tempP;

		if (tempP.is_valid)
		{
			m_buffer_enemy = tempP;
			std::cout << "Successfully received a valid packet.\n";
			return true;
		}
		else
		{
			std::cerr << "ERROR: Packet is invalid!\n";
			return false;
		}
	}
	return false;
}


OnlineUser::Default_packet OnlineUser::convert_to_Default_packet(const bool is_using_a_card, const Card& card,
	const Card::CardTyp wunsch_typ)
{
	OnlineUser::Default_packet temp;
	if (is_using_a_card)
		temp.uses_card = true;
	else
		temp.uses_card = false;

	temp.card_typ = card.getTyp();
	temp.card_rank = card.getRank();

	temp.wishcard_value = wunsch_typ;

	return temp;
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