#pragma once
#include "Card.hpp"
#include <vector>
#include <iostream>
#include "Logic.hpp"
#include "Client.hpp"
#include "Host.hpp"


class Player
{
public:

	Player(Logic* logic);

	void move_card(sf::Vector2f new_pos, int card_index);

	sf::Vector2f getCoord(bool& mouseLeftPressed);
	
	virtual void dealCard(int cardToDeal, std::vector<Card>& cardStack);
	
	void drawCard(const Card& card);
	
	int getHandSize();
	
	Card& getCard(int index);

	void set_moving_status(bool moving);

	std::vector<Card> m_playerHand;
	float m_xOffset{ 0.0 };
	float m_yOffset{ 0.0 };
	float m_xDefaultVal{ (windowSettings::windowX * 0.75f) };
	float m_yDefaultVal{ (windowSettings::windowY * 0.6f) };

protected:
	struct Move_card
	{
		bool currently_moving{ false };
		int index_of_card{ -1 };
	};

	Move_card move_info;
	Logic* m_logic;
};

