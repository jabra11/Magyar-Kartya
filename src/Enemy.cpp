#include "Enemy.hpp"
#include <chrono>

Enemy::Enemy(Logic *logic)
	:m_logic{logic}
{
}


void Enemy::dealCard(int cardToDeal, std::vector<Card> &cardStack)
{
	std::cout << "Gegner: " << m_enemyHand[cardToDeal] << " -> " << cardStack.back() << "\n\n";
	m_enemyHand[cardToDeal].setTexture();
	std::swap(Enemy::m_enemyHand[cardToDeal], Enemy::m_enemyHand.back());
	cardStack.push_back(m_enemyHand.back());
	Enemy::m_enemyHand.pop_back();
}

const int Enemy::getHandSize()
{
	return m_enemyHand.size();
}

void Enemy::drawCard(const Card &card)
{
	m_enemyHand.push_back(card);
	std::cout << "Gegner: Karte gezogen\n\n";

	std::array<std::string, 6> temp;

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size(); ++i)
	{
		temp[i] = m_logic->m_myFeed[i];
	}

	m_logic->m_myFeed[0] = "Gegner: Karte gezogen";

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size() - 1; ++i)
	{
		m_logic->m_myFeed[i + 1] = temp[i];
	}
}

Card& Enemy::getCard(int index)
{
	return m_enemyHand[index];
}

void Enemy::determineBestCard(const Card &topOfCardStack, int sizeOfPlayerHand,
	bool wunschKarteAktiv, const Card &wunschKarte, int schwierigkeitsGrad)
{

	// time the algorithm runtime
	// startpoint
	auto start = std::chrono::steady_clock::now();

	Card currentCard;
	std::vector<int> saveCardPoints;

	if (schwierigkeitsGrad == 0)
	{
		for (unsigned int i{ 0 }; i < m_enemyHand.size(); ++i)
		{
			int holdPoints{ 0 };
			if (m_enemyHand[i].getRank() == topOfCardStack.getRank())
				holdPoints += 10;

			if (wunschKarteAktiv)
			{
				if (m_enemyHand[i].getTyp() == wunschKarte.getTyp())
					holdPoints += 10;
			}

			else
				if (m_enemyHand[i].getTyp() == topOfCardStack.getTyp())
					holdPoints += 10;

			if (m_enemyHand[i].getRank() == topOfCardStack.getRank() &&
				m_enemyHand[i].getTyp() == topOfCardStack.getTyp())
				holdPoints -= 15;

			if (m_enemyHand[i].getRank() == Card::SIEBEN)
			{
				if (m_enemyHand.size() == 2)
					holdPoints += 10;

				else
					holdPoints -= 8;
			}

			if (m_enemyHand[i].getRank() == Card::BUBE)
			{
				if (sizeOfPlayerHand <= 3)
					holdPoints += 20;
				else
					holdPoints -= 20;
			}

			if (m_enemyHand[i].getRank() == Card::ASS)
			{
				holdPoints -= 5;
				int amountOfAces{ 0 };

				for (auto element : m_enemyHand)
				{
					if (element.getRank() == Card::ASS)
						++amountOfAces;
				}

				if (amountOfAces > 1)
					holdPoints += 2;
				else
					holdPoints += 1;
			}


			saveCardPoints.push_back(holdPoints);
		}
	}

	for (unsigned int startIndex{ 0 }; startIndex < (saveCardPoints.size() - 1); ++startIndex)
	{
		int heightestIndex = startIndex;

		for (unsigned int currentIndex = startIndex + 1; currentIndex < saveCardPoints.size(); ++currentIndex)
		{
			if (saveCardPoints[currentIndex] > saveCardPoints[heightestIndex])
				heightestIndex = currentIndex;
		}

		std::swap(saveCardPoints[startIndex], saveCardPoints[heightestIndex]);
		std::swap(m_enemyHand[startIndex], m_enemyHand[heightestIndex]);
	}

	// endpoint
	auto end = std::chrono::steady_clock::now();
	std::cout << "Calculated best move in " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << " microseconds.\n";
}

void Enemy::determineBesteWunschKarte(const Card &card, Card &wunschKarte)
{
	int amountPiros{ 0 };
	int amountMock{ 0 };
	int amountTOECK{ 0 };
	int amountZOELD{ 0 };

	for (unsigned int i{ 0 }; i < m_enemyHand.size(); ++i)
	{
		if (m_enemyHand[i].getRank() == Card::SIEBEN)
			continue;

		switch (m_enemyHand[i].getTyp())
		{
		case Card::PIROS:	++amountPiros;	break;
		case Card::MOCK:	++amountMock;	break;
		case Card::TOECK:	++amountTOECK;	break;
		case Card::ZOELD:	++amountZOELD;	break;
		}
	}


	wunschKarte = card;

	if (amountZOELD > amountPiros && amountZOELD > amountMock && amountZOELD > amountTOECK)
		wunschKarte.setTyp(Card::ZOELD);
	else if (amountMock > amountPiros && amountMock > amountTOECK && amountMock > amountZOELD)
		wunschKarte.setTyp(Card::MOCK);
	else if (amountTOECK > amountPiros && amountTOECK > amountMock && amountTOECK > amountZOELD)
		wunschKarte.setTyp(Card::TOECK);
	else 
		wunschKarte.setTyp(Card::PIROS);
}