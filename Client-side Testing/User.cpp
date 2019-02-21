#include "User.h"


User::User(const sf::IpAddress &addressOfOtherUser)
	:m_addressOfOtherUser{addressOfOtherUser}
{
}

void User::connectToOtherGuy()
{
	m_mySocket.connect(m_addressOfOtherUser, 50000);
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
