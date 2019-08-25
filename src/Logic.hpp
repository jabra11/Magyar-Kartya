#pragma once
#include "Card.hpp"

class Logic
{
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

	bool m_playersTurn{ true };
	bool m_enemysTurn{ false };

	Logic();

	const std::string& getFeedString(int index) const;

	//player true, enemy false
	const bool validateMove(const Card &cardToValidate, const Card &cardOnStack, bool player, bool playerHasToDraw = false); 

	const bool playerSkips() const;
	const bool enemySkips() const; 

	void resetFeed();

	void resetStatuses();

	void setStatuses(const Card &card, bool player);

	const Card& getWunschkarte() const;
	void setWunschkarte(Card &card, bool player);
	void setWunschkarte(Card &card);

	const sf::Sprite& getWunschkarteSprite();

	const bool wunschkarteAktiv();

	const bool viewEnemyHand() const;

	const std::string getWunschkartenName() const;

	// Decapsulate
	friend class Player;
	friend class Enemy;
	friend class OnlinePlayer;
	friend class OnlineEnemy;

private:

	int m_wunschKarteSpam{ 1 };

	std::array<std::string, 6> m_myFeed{ "" };
};

