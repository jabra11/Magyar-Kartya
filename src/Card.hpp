#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <array>
#include "textureArray.hpp"
#include "windowSettings.hpp"


class Card
{
public:
	enum CardTyp
	{
		ZOELD,
		TOECK,
		MOCK,
		PIROS,
		MAX_TYPES,
		PLACEHOLDER_TYP
	};
	enum CardRank
	{
		DAME,
		KOENIG,
		BUBE,
		SIEBEN,
		ACHT,
		NEUN,
		ZEHN,
		ASS,
		MAX_RANKS,
		PLACEHOLDER_RANK
	};


private:
	CardRank m_rank;
	CardTyp m_typ;
public:
	sf::Sprite m_graphicalCard;
public:

	Card(const CardTyp &typ = CardTyp::MAX_TYPES, const CardRank &rank = CardRank::MAX_RANKS,
		float xPos = 280.0f, float yPos = 550.0f, bool canBeMoved = true);
	
	bool m_canBeMoved{ false };

	// set a texture based on parameter input
	void setTexture(const sf::Texture &texture);

	// set texture based on m_rank and m_typ, this is called in the constructor
	void setTexture();							
	
	const std::string getCardName() const;
	const CardTyp& getTyp() const;
	void setTyp(const CardTyp &typ);

	CardRank getRank() const;
	void setRank(const CardRank &rank);

	sf::Sprite& getGraphicalCard();

	friend std::ostream& operator<<(std::ostream &out, const Card &card);
	friend std::ostream& operator<<(std::ostream &out, const Card::CardTyp &typ);

	void setPosition(float xPos, float yPos);
};