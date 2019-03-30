#pragma once
#include <vector>
#include "Card.h"


class Deck
{
private:
public:
	std::vector<Card> m_deck;

	Card m_temp;
public:

	Deck();
	


	Card& dealCard(std::vector<Card> &cardStack);
	Card& dealCard(float xPos,float yPos, std::vector<Card> &cardStack);
	Card& dealCard(sf::Vector2f vector, std::vector<Card> &cardStack);
	void shuffleDeck();

	unsigned int getSize() const;

	Card& getLastCard();

	static const int getRandomNumber(unsigned int min, unsigned int max);
	static void swapCard(Card &a, Card &b);

	void shuffleStack(std::vector<Card> &cardStack);

	Card& operator[](int index);
};

