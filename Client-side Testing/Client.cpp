#include "Client.h"


Client::Client(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> *pointerToDeck,
	std::vector<CardInfo> *pointerToHand)
	:User{addressOfOtherGuy, pointerToDeck, pointerToHand}
{
}

void Client::receiveDeckInfo()
{
	std::vector<sf::Packet> packetsContainingTheDeck;
	
	unsigned const int deckSize{ 32 };
	for (int i{ 0 }; i < deckSize; ++i)
	{
		// receive packets containing the cardInfo of the whole deck and read them into the std::vector
		sf::Packet temp;
		m_mySocket.receive(temp);
		packetsContainingTheDeck.push_back(temp);
	}

	// now extract the cardInfo from the packets

	for (int i{ 0 }; i < packetsContainingTheDeck.size(); ++i)
	{
		CardInfo temp;
		packetsContainingTheDeck[i] >> temp;
		m_copyOfTheDeck.push_back(temp);
	}

	assert(m_copyOfTheDeck.size() == 32 && "CardInfoCopyOfTheDeck is not of size 32.\n");
}