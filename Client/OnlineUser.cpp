#include "OnlineUser.h"



OnlineUser::OnlineUser(int port)
	:m_port{port}
{
}


sf::Packet& operator<<(sf::Packet &packet, const OnlineUser::Default_packet &card)
{
	return packet << card.uses_card << card.card_rank << card.card_typ << card.wunschkarte_value;
}


sf::Packet& operator>>(sf::Packet &packet, OnlineUser::Default_packet &card)
{
	return packet >> card.uses_card >> card.card_rank >> card.card_typ >> card.wunschkarte_value;
}


void OnlineUser::send_choice_information(const bool is_using_a_card, const Card& card,
	const Card::CardTyp wunsch_typ)
{

	sf::Packet temp;
	temp << convert_to_Default_packet(is_using_a_card, card, wunsch_typ);

	std::cout << "Sending packet..\n";
	if (m_socket.send(temp) == sf::Socket::Done)
		std::cout << "Successfully sent packet.\n";

	else
		std::cerr << "ERROR: Couldn't send the packet.\n";
}


void OnlineUser::receive_choice_information(OnlineUser::Default_packet& Default_packet_to_write_in,
	const bool is_using_a_card, const Card& card,
	const Card::CardTyp wunsch_typ)
{
	sf::Packet temp;
	if (m_socket.receive(temp) == sf::Socket::Done)
		std::cout << "Successfully received a packet.\n";

	else
		std::cerr << "ERROR: Did not receive any packet.\n";

	temp >> Default_packet_to_write_in;
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

	temp.wunschkarte_value = wunsch_typ;

	return temp;
}