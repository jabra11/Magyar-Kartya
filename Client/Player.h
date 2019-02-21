#pragma once
#include "Card.h"
#include <vector>
#include <iostream>
#include "Logic.h"

class Player
{
private:
	Logic *m_logic;
public:
	std::vector<Card> m_playerHand;
	float m_xOffset{ 0.0 };
	float m_yOffset{ 0.0 };

	float m_xDefaultVal{ (windowSettings::windowX * 0.75f) };
	float m_yDefaultVal{ (windowSettings::windowY * 0.6f) };

public:

	Player(Logic *logic);
	sf::Vector2f getCoord(bool &mouseLeftPressed);

	void dealCard(int cardToDeal, std::vector<Card> &cardStack);
	void drawCard(const Card &card, const std::vector<Card> &deck);
	const int getHandSize();

	Card& getCard(int index);
};

