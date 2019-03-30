#include "Deck.h"
#include <random>
#include <cassert>


Deck::Deck()
{
	int temp{ 0 };
	for (int typ{ 0 }; typ < Card::MAX_TYPES; ++typ)
		for (int rank{ 0 }; rank < Card::MAX_RANKS; ++rank)
		{
			m_deck.push_back(Card(static_cast<Card::CardTyp>(typ),static_cast<Card::CardRank>(rank)));
		}

	shuffleDeck();
	std::cout << "Deck wurde gemischt\n";
}

void Deck::shuffleDeck()
{
	for (Card &card : m_deck)
	{
		swapCard(card, m_deck[getRandomNumber(0, (m_deck.size() - 1))]);
	}
}

void Deck::swapCard(Card &a, Card &b)
{
	static Card temp;
	temp = a;
	a = b;
	b = temp;
}

Card& Deck::getLastCard()
{
	return m_deck.back();
}


const int Deck::getRandomNumber(unsigned int min, unsigned int max)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> randomCard(min, max);
	return randomCard(mersenne);
}

Card &Deck::dealCard(std::vector<Card> &cardStack)
{
	m_temp = m_deck.back();
	m_deck.pop_back();
	//std::cout << "size of deck" << m_deck.size() << "\n";
	return m_temp;
}

Card& Deck::dealCard(sf::Vector2f vector, std::vector<Card> &cardStack)
{
	bool shuffle{ false };
	if (m_deck.size() == 1)
		shuffle = true;

	m_deck.back().setPosition(vector.x, vector.y);
	m_temp = m_deck.back();
	m_deck.pop_back();

	if (shuffle)
		shuffleStack(cardStack);

	return m_temp;
}

Card &Deck::dealCard(float x, float y, std::vector<Card> &cardStack)
{
	bool shuffle{ false };
	if (m_deck.size() == 1)
		shuffle = true;

	m_deck.back().setPosition(x, y);
	m_temp = m_deck.back();
	m_deck.pop_back();

	if (shuffle)
		shuffleStack(cardStack);

	return m_temp;
}

void Deck::shuffleStack(std::vector<Card> &cardStack)
{
	assert(cardStack.size() > 0 && "CardStack has no MEMBERS!!!!!!!");
	m_deck.clear();
	Card temp;
	temp = cardStack.back();
	cardStack.pop_back();
	unsigned int size(cardStack.size());
	for (unsigned int i{ 0 }; i < size; ++i)
	{
		m_deck.push_back(cardStack.back());
		cardStack.pop_back();
	}
	cardStack.clear();
	cardStack.push_back(temp);
	shuffleDeck();
	std::cout << "Das Deck wird neu gemischt...\n";
	std::cout << '\n';
}

unsigned int Deck::getSize() const
{
	return m_deck.size();
}

Card& Deck::operator[](int index)
{
	return m_deck[index];
}