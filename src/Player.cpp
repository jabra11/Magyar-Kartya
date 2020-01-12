#include "Player.hpp"

Player::Player(Logic *logic)
	:m_logic{ logic }
{
}

void Player::move_card(sf::Vector2f new_pos, int card_index)
{
	if (move_info.currently_moving && move_info.index_of_card != card_index)
		getCard(move_info.index_of_card).setPosition(new_pos.x, new_pos.y);

	else if (move_info.currently_moving && move_info.index_of_card == card_index)
		getCard(card_index).setPosition(new_pos.x, new_pos.y);

	else
	{
		move_info.currently_moving = true;
		move_info.index_of_card = card_index;
		getCard(card_index).setPosition(new_pos.x, new_pos.y);
	}
}

void Player::dealCard(int cardToDeal, std::vector<Card> &cardStack)
{
	std::cout << "You: " << m_playerHand[cardToDeal] << " -> " << cardStack.back() << "\n";
	std::swap(Player::m_playerHand[cardToDeal], Player::m_playerHand.back());
	cardStack.push_back(m_playerHand.back());
	Player::m_playerHand.pop_back();
}

int Player::getHandSize()
{
	return m_playerHand.size();
}

void Player::drawCard(const Card &card)
{
	m_playerHand.push_back(card);
	std::cout << "You draw " << card << "\n";

	std::array<std::string, 6> temp;

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size(); ++i)
	{
		temp[i] = m_logic->m_myFeed[i];
	}

	m_logic->m_myFeed[0] = "You: Draw card";

	for (unsigned int i{ 0 }; i < m_logic->m_myFeed.size() - 1; ++i)
	{
		m_logic->m_myFeed[i + 1] = temp[i];
	}
}

Card& Player::getCard(int index)
{
	return m_playerHand[index];
}

void Player::set_moving_status(bool moving)
{
	move_info.currently_moving = moving;
}

sf::Vector2f Player::getCoord(bool &mouseLeftPressed)
{
	bool noSpace{ false };
	mouseLeftPressed = false;
	do
	{
		for (int outer{ 0 }; outer < getHandSize(); ++outer)
		{
			if (static_cast <int>(getCard(outer).getGraphicalCard().getPosition().x) ==
				static_cast<int>(m_xDefaultVal + m_xOffset) &&
				static_cast <int>(getCard(outer).getGraphicalCard().getPosition().y) ==
				static_cast<int>(m_yDefaultVal + m_yOffset))
			{				
				noSpace = true;
				break;
			}

			if (noSpace)
				break;
			else
				noSpace = false;
		}

		if (noSpace)
		{
			if (m_xOffset == 3 * 75)
			{
				m_yOffset += 75;
				m_xOffset = 0;
			}
			else
			{
				m_xOffset += 75;
			}
			noSpace = false;
		}
		else
		{
			m_xOffset = 0;
			m_yOffset = 0;
		}
	} while (noSpace);

	return sf::Vector2f(m_xDefaultVal+m_xOffset,m_yDefaultVal+ m_yOffset);
}