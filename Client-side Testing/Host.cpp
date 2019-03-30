#include "Host.h"

Host::Host(const sf::IpAddress &addressOfOtherGuy, std::vector<CardInfo> &pointerToDeck,
	std::vector<CardInfo> &pointerToHand)
	:User{addressOfOtherGuy, pointerToDeck, pointerToHand}
{
}

void Host::sendDeckInfo()
{
	std::vector<sf::Packet> packetsContainingDeckInfo;

	for (unsigned int i{ 0 }; i < m_pointerToDeck.size(); ++i)
	{
		sf::Packet temp;
		temp << m_pointerToDeck[i];
		packetsContainingDeckInfo.push_back(temp);
	}

	assert(packetsContainingDeckInfo.size() == 32 && "Size of packet vector is not 32!!");

	int packetsSentCounter{ 0 };

	for (unsigned int i{ 0 }; i < packetsContainingDeckInfo.size(); ++i)
	{
		while (m_mySocket.send(packetsContainingDeckInfo[i]) != sf::Socket::Done)
			std::cerr << "Couldn't send packet #" << ++packetsSentCounter << std::endl;

		std::cout << "Successfully sent packet #" << ++packetsSentCounter << std::endl;
	}
}

void Host::connectToOtherGuy()
{
	while (m_myListener.listen(50000, m_addressOfOtherUser) != sf::Socket::Done)
		std::cerr << "No connection attemps received on port 50000\n";

	if (m_myListener.accept(m_mySocket) == sf::Socket::Done)
		std::cout << "Successfully connected\n";
}