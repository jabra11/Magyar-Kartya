#include "Host.h"

Host::Host(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> *pointerToDeck,
	std::vector<CardInfo> *pointerToHand)
	:User{addressOfOtherGuy, pointerToDeck, pointerToHand}
{
}

void Host::sendDeckInfo()
{
	std::vector<sf::Packet> packetsContainingDeckInfo;

	for (int i{ 0 }; i < m_pointerToDeck->size(); ++i)
	{
		sf::Packet temp;
		temp << (*m_pointerToDeck)[i];
		packetsContainingDeckInfo.push_back(temp);
	}

	assert(packetsContainingDeckInfo.size() == 32 && "Size of packet vector is not 32!!");

	for (int i{ 0 }; i < packetsContainingDeckInfo.size(); ++i)
	{
		m_mySocket.send(packetsContainingDeckInfo[i]);
	}
}