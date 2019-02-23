#pragma once
#include "Card.h"

class Logic
{
private:
	int m_wunschKarteSpam{ 1 };

	std::array<std::string, 6> m_myFeed{ "" };
public:
	bool m_startWunschKarteAktiv{ false };
	bool m_wunschkarteAktiv{ false };
	Card m_wunschkarte{Card::PIROS, Card::SIEBEN};

	bool m_playerSkips{ false };
	bool m_enemySkips{ false };

	bool m_playerHasToDraw{ false };
	bool m_enemyHasToDraw{ false };
	int m_amountOfCardsToDraw{ 0 };

	bool m_viewEnemyHand{ false };

	sf::Sprite m_SpriteWunschkarte;
	int m_sizeOfStartHand{ 5 };

public:
	bool m_playersTurn{ true };
	bool m_enemysTurn{ false };

public:
	Logic();

	const std::string& getFeedString(int index) const;

	const bool validateMove(const Card &cardToValidate, const Card &cardOnStack, bool player, bool playerHasToDraw = false); //player true, enemy false

	const bool playerSkips() const;
	const bool enemySkips() const; 

	//void drawsCard(bool player);

	void resetFeed();

	void resetStatuses();

	void setStatuses(const Card &card, bool player);

	const Card& getWunschkarte() const;
	void setWunschkarte(Card &card, bool player);
	void setWunschkarte(Card &card);

	const sf::Sprite& getWunschkarteSprite();

	const bool wunschkarteAktiv();

	const bool viewEnemyHand() const;

	const std::string getWunschkartenName()
	{
		switch (m_wunschkarte.getTyp())
		{
		case Card::PIROS:   return "Wunschkarte aktiv: Piros"; break;
		case Card::TOECK:	return "Wunschkarte aktiv: Toeck"; break;
		case Card::MOCK:    return "Wunschkarte aktiv: Mock"; break;
		case Card::ZOELD:    return "Wunschkarte aktiv: Zoeld"; break;
		default: std::cout << "Could not get a name (getWunschkartenName())";
		}
	}
	
	friend class Player;
	friend class Enemy;
};

