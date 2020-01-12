#include "Deck.hpp"
#include <random>
#include <cassert>
#include <thread>

#include "Client.hpp"
#include "Host.hpp"
#include "OnlineUser.hpp"

Deck::Deck()
{
	constexpr int seed = 55000;
	std::mt19937 gen(seed);
	std::uniform_int_distribution<int> dis(0, 31);

	for (auto& element : number_list)
	{
		element = dis(gen);
	}

	for (int typ{ 0 }; typ < Card::MAX_TYPES; ++typ)
		for (int rank{ 0 }; rank < Card::MAX_RANKS; ++rank)
		{
			m_deck.push_back(Card(static_cast<Card::CardTyp>(typ),static_cast<Card::CardRank>(rank)));
		}

	shuffleDeck();
	std::cout << "The deck was shuffled\n";
}

void Deck::set_online_status(bool is_host, Host* host, Client* client)
{
	if (is_host)
		this->host = host;
	else
		this->client = client;
}

void Deck::shuffleDeck()
{
	if (client || host)
	{
		// shuffle deck based on a given list of numbers (number_list)
		for (unsigned int o = 0; o < this->getSize(); ++o)
		{
			for (unsigned int i = 0; i < number_list.size(); ++i)
			{
				if (number_list[i] <= this->getSize() - 1)
				{
					swapCard(m_deck[o], m_deck[number_list[i]]);
					
					std::swap(number_list[i], number_list.back());
				}
			}
		}
	}
	else
	{
		for (Card& card : m_deck)
		{
			swapCard(card, m_deck[getRandomNumber(0, (m_deck.size() - 1))]);
		}
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


int Deck::getRandomNumber(unsigned int min, unsigned int max)
{
	std::random_device rd;
	std::mt19937 mersenne(rd());
	std::uniform_int_distribution<> randomCard(min, max);
	return randomCard(mersenne);
}

Card& Deck::dealCard()
{
	m_temp = m_deck.back();
	m_deck.pop_back();
	return m_temp;
}

Card& Deck::dealCard(const sf::Vector2f& vector, std::vector<Card> &cardStack)
{
	bool shuffle{ false };
	if (m_deck.size() == 1)
		shuffle = true;

	m_deck.back().setPosition(vector.x, vector.y);
	m_temp = m_deck.back();
	m_deck.pop_back();

	if (shuffle)
	{
		shuffleStack(cardStack);
	}
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

	std::cout << "Shuffle deck...\n";
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