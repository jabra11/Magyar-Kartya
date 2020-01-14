#include "Logic.hpp"

Logic::Logic()
{
	m_SpriteWunschkarte.setPosition(sf::Vector2f(50, 300));
}

bool Logic::validateMove(const Card &cardToValidate, const Card &cardOnStack, bool player, bool playerHasToDraw)
{
	if ((playerHasToDraw) ? cardToValidate.getRank() == Card::BUBE :
		(m_startWunschKarteAktiv) ? true :
		(m_wunschkarteAktiv) ? cardToValidate.getTyp() == m_wunschkarte.getTyp() ||
		cardToValidate.getRank() == m_wunschkarte.getRank() :
		cardToValidate.getTyp() == cardOnStack.getTyp() ||
		cardToValidate.getRank() == cardOnStack.getRank() ||
		cardToValidate.getRank() == Card::SIEBEN)
	{	
		std::array<std::string, 6> temp;
		
		for (unsigned int i{ 0 }; i < m_myFeed.size(); ++i)
		{
			temp[i] = m_myFeed[i];
		}

		if (player)
			m_myFeed[0] = "You: " + cardToValidate.getCardName() + " -> " + cardOnStack.getCardName();
		else
			m_myFeed[0] = "Enemy: " + cardToValidate.getCardName() + " -> " + cardOnStack.getCardName();

		for (unsigned int i{ 0 }; i < m_myFeed.size() - 1; ++i)
			m_myFeed[i + 1] = temp[i];

		return true;
	}
	else
		return false;
}


const std::string& Logic::getFeedString(int index) const
{
	return m_myFeed[index];
}

void Logic::setStatuses(const Card &card, bool player)
{
	if (card.getRank() == Card::BUBE)
	{
		m_amountOfCardsToDraw += 2;
		if (player)
		{
			m_enemyHasToDraw = true;
			m_playerHasToDraw = false;
		}
		else
		{
			std::cout << "player has to draw " << m_amountOfCardsToDraw << " Cards\n";
			m_playerHasToDraw = true;
			m_enemyHasToDraw = false;
		}
	}

	if (card.getRank() == Card::ASS)
	{
		if (player)
			m_enemySkips = true;
		else
			m_playerSkips = true;
	}
}

void Logic::resetFeed()
{
	for (auto &element : m_myFeed)
		element = "";
}

void Logic::resetStatuses()
{
	m_playersTurn = true;
	m_enemysTurn = false;

	m_startWunschKarteAktiv = false;
	m_wunschkarteAktiv = false;

	m_playerSkips = false;
	m_enemySkips = false;

	m_playerHasToDraw = false;
	m_enemyHasToDraw = false;

	m_amountOfCardsToDraw = 0;
}

bool Logic::viewEnemyHand() const 
{
	if (m_viewEnemyHand)
		return true;
	else
		return false;
}

bool Logic::playerSkips() const 
{
	if (m_playerSkips)
		return true;
	else
		return false;
}

bool Logic::enemySkips() const 
{
	if (m_enemySkips)
		return true;
	else
		return false;
}

const Card& Logic::getWunschkarte() const
{
	return m_wunschkarte;
}

void Logic::setWunschkarte(Card &card, bool player)
{

	m_wunschkarte = card;
	if (player)
		std::cout << "Du willst " << card.getTyp() << ".\n";

	else
		std::cout << "Der Gegner will " << card.getTyp() << ".\n";
}

bool Logic::wunschkarteAktiv()
{
	if (m_wunschkarteAktiv)
	{
		switch (m_wunschkarte.getTyp())
		{
		case Card::MOCK: m_SpriteWunschkarte.setTexture(otherTextureArr[myTextures::OtherTextures::WUNSCHKARTE_AKTIV_MOCK], true); break;
		case Card::ZOELD: m_SpriteWunschkarte.setTexture(otherTextureArr[myTextures::OtherTextures::WUNSCHKARTE_AKTIV_ZOELD], true); break;
		case Card::TOECK: m_SpriteWunschkarte.setTexture(otherTextureArr[myTextures::OtherTextures::WUNSCHKARTE_AKTIV_TOECK], true); break;
		case Card::PIROS: m_SpriteWunschkarte.setTexture(otherTextureArr[myTextures::OtherTextures::WUNSCHKARTE_AKTIV_PIROS], true); break;
		default: throw std::runtime_error("Error in Logic::wunschkarteAktiv");
		}
	}
		
	return m_wunschkarteAktiv;
}

void Logic::setWunschkarte(Card &card)
{
	m_wunschkarte = card;
}

const sf::Sprite& Logic::getWunschkarteSprite() const
{
	return m_SpriteWunschkarte;
}

std::string Logic::getWunschkartenName() const
{
    switch (m_wunschkarte.getTyp())
    {
        case Card::PIROS:	return "Wunschkarte aktiv: Piros";	break;
        case Card::TOECK:	return "Wunschkarte aktiv: Toeck";	break;
        case Card::MOCK:    return "Wunschkarte aktiv: Mock";	break;
        case Card::ZOELD:	return "Wunschkarte aktiv: Zoeld";	break;
        default: throw std::runtime_error{"Could not get a name (getWunschkartenName())"};
    }
}
