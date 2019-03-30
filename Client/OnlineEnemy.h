#pragma once
#include <vector>

#include "Logic.h"
#include "Card.h"
#include "SFML/Network.hpp"

class OnlineEnemy
{

public:

	OnlineEnemy(Logic *logic);

	void getNextMove(const sf::Packet &packet);
	const int getHandSize();

	void dealCard(int index);
	void drawCard(const Card& card);

private:

	std::vector<Card> m_enemyHand;
	float m_yOffSet{ 0.0f };
	float m_xOffset{ 0.0f };

	float m_xDefaultVal{};
	float m_yDefaultVal{};
};

