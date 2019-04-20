#pragma once
#include <vector>

#include "Logic.h"
#include "Card.h"
#include "SFML/Network.hpp"
#include "Client.h"
#include "Host.h"

class OnlineEnemy
{

public:

	OnlineEnemy(Host* host, Client* client, Logic* logic, Deck* deck, std::vector<Card>* card_stack, int port, bool is_hosting);

	void getNextMove();
	const int getHandSize();

	void dealCard(int index);
	void drawCard(const Card& card);

	std::vector<Card> m_enemyHand;
	float m_yOffSet{ 0.0f };
	float m_xOffset{ 0.0f };

	float m_xDefaultVal{};
	float m_yDefaultVal{};

	Logic* m_logic;
	Deck* m_deck;
	std::vector<Card>* m_card_stack;

	Client* m_client;
	Host* m_host;

	bool m_is_hosting{ false };
};

