#include "User.h"


User::User(const sf::IpAddress &addressOfOtherUser, std::vector<CardInfo> &pointerToDeck,
	std::vector<CardInfo> &pointerToHand )
	:m_addressOfOtherUser{addressOfOtherUser}, m_pointerToDeck{pointerToDeck}, m_poiterToHand{pointerToHand}
{
}

void User::connectToOtherGuy()
{
	while (m_mySocket.connect(m_addressOfOtherUser, 50000, sf::Time{ sf::milliseconds(100) }) != sf::Socket::Done)
		std::cerr << "Could not connect\n";

	std::cout << "Successfully connected\n";
}

void User::sendCardInformation(const CardInfo &card)
{
	sf::Packet cardData;
	cardData << card;
	m_mySocket.send(cardData);
}

void User::receiveCardInformation(CardInfo &card)
{
	sf::Packet cardData;
	m_mySocket.receive(cardData);
	cardData >> card;
}

sf::Packet& operator<<(sf::Packet &packet, const User::CardInfo &card)
{
	return packet << card.cardTyp << card.cardRank << card.wunschKarte;
}

sf::Packet& operator>>(sf::Packet &packet, User::CardInfo &card)
{
	return packet >> card.cardTyp >> card.cardRank >> card.wunschKarte;
}
