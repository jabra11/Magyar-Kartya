#pragma once

#include "SFML/Network.hpp"
#include <vector>
#include <array>
#include <cassert>
#include <iostream>

class User
{
public:
	enum CardTyp
	{
		ZOELD,
		TOECK,
		MOCK,
		PIROS,
		MAX_TYPES,
		IGNORE_TYP
	};
	enum CardRank
	{
		DAME,
		KOENIG,
		BUBE,
		SIEBEN,
		ACHT,
		NEUN,
		ZEHN,
		ASS,
		MAX_RANKS,
		IGNORE_RANK
	};
	
public:
	struct CardInfo
	{
		int cardTyp;
		int cardRank;
		int wunschKarte{ static_cast<int>(CardTyp::IGNORE_TYP) };
	};
	
protected:
	sf::TcpSocket m_mySocket;
	sf::IpAddress m_addressOfOtherUser;

	std::vector<CardInfo> m_pointerToDeck;
	std::vector<CardInfo> m_poiterToHand;

public:
	User(const sf::IpAddress &addressOfOtherUser, std::vector<CardInfo> &pointerToDeck,
		std::vector<CardInfo> &pointerToHand);

	void sendCardInformation(const CardInfo &cardToSend);
	void receiveCardInformation(CardInfo &cardToReceive);

	virtual void connectToOtherGuy();

	friend sf::Packet& operator<<(sf::Packet &packet, const CardInfo &card);
	friend sf::Packet& operator>>(sf::Packet &packet, CardInfo &card);
};

