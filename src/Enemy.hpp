#pragma once
#include <vector>	
#include "Card.hpp"
#include <iostream>
#include "Logic.hpp"

class Enemy
{
private:
	Logic *m_logic;

public:
	std::vector<Card> m_enemyHand;
	float m_yOffset{ 0.0 };
	float m_xOffset{ 0.0 };

	float m_xDefaultVal{};
	float m_yDefaultVal{};


public:
	Enemy(Logic *logic);

	void dealCard(int cardToDeal, std::vector<Card> &cardStack);
	void drawCard(const Card &card);
	const int getHandSize();

	void determineBestCard(const Card &topOfCardStack, int sizeOfPlayerHand,
		bool wunschkarteAktiv, const Card &wunschKarte, int schwierigkeitsgrad = 0);

	void determineBesteWunschKarte(const Card &card, Card &wunschkarte);

	Card& getCard(int index);
};


