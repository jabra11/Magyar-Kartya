#include "OnlineUser.h"



OnlineUser::OnlineUser()
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

void OnlineUser::send_card_information(const OnlineUser::Default_packet& packet_to_send)
{
	sf::Packet temp;
	temp << packet_to_send;

	std::cout << "Sending packet..\n";
	if (m_my_socket.send(temp) == sf::Socket::Done)
		std::cout << "Successfully sent packet.\n";

	else
		std::cerr << "ERROR: Could not send packet.\n";
}

void OnlineUser::receive_card_information(OnlineUser::Default_packet& packet_to_receive)
{
	sf::Packet temp;
	if (m_my_socket.receive(temp) == sf::Socket::Done)
		std::cout << "Successfully received a packet.\n";

	else
		std::cerr << "ERROR: Did not receive any packet.\n";
}
