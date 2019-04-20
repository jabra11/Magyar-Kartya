#pragma once
#include <vector>

#include "OnlineUser.h"

class OnlineUser;
class Host;
class Client;

class Deck
{
private:
public:
	std::vector<Card> m_deck;

	Card m_temp;
public:

	Deck();
	


	Card& dealCard();
	Card& dealCard(float xPos, float yPos, std::vector<Card>& cardStack, Client* client = nullptr, Host* host = nullptr);
	Card& dealCard(sf::Vector2f vector, std::vector<Card>& cardStack, Client* client = nullptr, Host* host = nullptr);
	void shuffleDeck();

	unsigned int getSize() const;

	Card& getLastCard();

	static const int getRandomNumber(unsigned int min, unsigned int max);
	static void swapCard(Card &a, Card &b);

	void shuffleStack(std::vector<Card> &cardStack);

	Card& operator[](int index);
};

