#pragma once
#include <vector>

#include "Logic.hpp"
#include "Card.hpp"
#include "SFML/Network.hpp"
#include "Client.hpp"
#include "Host.hpp"

class OnlineEnemy
{

public:

	OnlineEnemy(Host* host, Client* client, Logic* logic, Deck* deck, std::vector<Card>* card_stack, bool is_hosting);

	void getNextMove(sf::Socket::Status* error_flag);
	int getHandSize();

	void dealCard(int index);
	void drawCard(const Card& card);

	std::vector<Card> m_enemyHand;
	float m_yOffSet{ 0.0f };
	float m_xOffset{ 0.0f };

	float m_xDefaultVal{};
	float m_yDefaultVal{};

	Client* m_client;
	std::vector<Card>* m_card_stack;
	Host* m_host;
	Logic* m_logic;
	Deck* m_deck;


	bool m_is_hosting{ false };
};

