#include "Client.h"


Client::Client(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> &pointerToDeck,
	std::vector<CardInfo> &pointerToHand)
	:User{addressOfOtherGuy, pointerToDeck, pointerToHand}
{
}

void Client::receiveDeckInfo()
{
	std::vector<sf::Packet> packetsContainingTheDeck;
	
	int packetsReceivedCounter{ 0 };
	unsigned const int deckSize{ 32 };
	for (int i{ 0 }; i < deckSize; ++i)
	{
		// receive packets containing the cardInfo of the whole deck and read them into the std::vector
		sf::Packet temp;
		while (m_mySocket.receive(temp) != sf::Socket::Done)
			std::cerr << "Didn't receive any packet\n";

		std::cout << ++packetsReceivedCounter << ". successfully received packet #" << packetsReceivedCounter << "\n";
		packetsContainingTheDeck.push_back(temp);
	}

	// now extract the cardInfo from the packets

	for (unsigned int i{ 0 }; i < packetsContainingTheDeck.size(); ++i)
	{
		CardInfo temp;
		packetsContainingTheDeck[i] >> temp;
		m_copyOfTheDeck.push_back(temp);
	}

	assert(m_copyOfTheDeck.size() == 32 && "CardInfoCopyOfTheDeck is not of size 32.\n");
}

void Client::printDeck()
{
	int counter{ 0 };
	
	std::cout << "contents of Deck:\n";
	for (unsigned int i{ 0 }; i < m_copyOfTheDeck.size(); ++i)
	{
		std::cout << "#" << ++counter << " " << m_copyOfTheDeck[i].cardRank << " " << m_copyOfTheDeck[i].cardTyp << " " << m_copyOfTheDeck[i].wunschKarte << std::endl;
	}
}