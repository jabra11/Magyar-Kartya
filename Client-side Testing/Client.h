#pragma once
#pragma once

#include "SFML/Network.hpp"

class Client
{
public:
	/*enum CardTyp
	{
		Z�LD,
		T�CK,
		MOCK,
		PIROS,
		MAX_TYPES,
		IGNORE
	};
	enum CardRank
	{
		DAME,
		K�NIG,
		BUBE,
		SIEBEN,
		ACHT,
		NEUN,
		ZEHN,
		ASS,
		MAX_RANKS,
		IGNORE
	};

	struct CardInfo
	{
		CardTyp typ;
		CardRank rank;
		CardTyp typForWunschkarte{ IGNORE };
	};*/

private:
	sf::TcpSocket m_mySocket;
	sf::IpAddress m_addressOfHost;

public:
	Client(const sf::IpAddress &addressOfHost);


};