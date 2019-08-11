#include "Card.hpp"


Card::Card(const CardTyp &typ, const CardRank &rank, float xPos, float yPos, bool canBeMoved)
	:m_typ{typ}, m_rank{rank}, m_canBeMoved{canBeMoved}
{
	setTexture();

	m_graphicalCard.setOrigin((m_graphicalCard.getGlobalBounds().width / 2), (m_graphicalCard.getGlobalBounds().height / 2));
	m_graphicalCard.scale(0.4f, 0.4f);
	m_graphicalCard.setPosition(xPos, yPos);
}

void Card::setTexture(const sf::Texture &texture)
{
	m_graphicalCard.setTexture(texture);
}

void Card::setTexture()
{
	using namespace myTextures;
	switch (m_typ)
	{
	case ZOELD:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[ZOELD][DAME], true); break;
		case CardRank::KOENIG:	m_graphicalCard.setTexture(textureArr[ZOELD][KOENIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[ZOELD][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[ZOELD][SIEBEN], true); break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[ZOELD][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[ZOELD][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[ZOELD][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[ZOELD][ASS], true); break;
		default:				std::cout << "error in setTexture case ZOELD switch"; break;
		}
		break;
	}

	case TOECK:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[TOECK][DAME], true); break;
		case CardRank::KOENIG:	m_graphicalCard.setTexture(textureArr[TOECK][KOENIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[TOECK][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[TOECK][SIEBEN], true);  break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[TOECK][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[TOECK][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[TOECK][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[TOECK][ASS], true); break;
		default:				std::cout << "error in setTexture case TOECK switch"; break;
		}
		break;
	}

	case MOCK:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[MOCK][DAME], true); break;
		case CardRank::KOENIG:	m_graphicalCard.setTexture(textureArr[MOCK][KOENIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[MOCK][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[MOCK][SIEBEN], true); break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[MOCK][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[MOCK][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[MOCK][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[MOCK][ASS], true); break;
		default:				std::cout << "error in setTexture case MOCK switch"; break;
		}
		break;
	}

	case PIROS:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[PIROS][DAME], true); break;
		case CardRank::KOENIG:	m_graphicalCard.setTexture(textureArr[PIROS][KOENIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[PIROS][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[PIROS][SIEBEN], true); break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[PIROS][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[PIROS][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[PIROS][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[PIROS][ASS], true); break;
		default:				std::cout << "error in setTexture case PIROS switch"; break;
		}
		break;
	}

	default: break;
	}
}

const Card::CardTyp& Card::getTyp() const
{
	return m_typ;
}

void Card::setTyp(const CardTyp &typ)
{
	m_typ = typ;
}

Card::CardRank Card::getRank() const
{
	return m_rank;
}

void Card::setRank(const CardRank &rank)
{
	m_rank = rank;
}

sf::Sprite& Card::getGraphicalCard()
{
	return m_graphicalCard;
}

std::ostream& operator<<(std::ostream &out, const Card &card)
{
	switch (card.m_rank)
	{
	case Card::ASS:		out	<< "Ace";		break;
	case Card::ZEHN:	out	<< "X";			break;
	case Card::NEUN:	out	<< "IX";		break;
	case Card::ACHT:	out	<< "VIII";		break;
	case Card::SIEBEN:	out	<< "VII";		break;
	case Card::KOENIG:	out	<< "King";	break;
	case Card::DAME:	out	<< "Queen";		break;
	case Card::BUBE:	out	<< "Jack";		break;
	}

	out << " ";

	switch (card.m_typ)
	{
	case Card::ZOELD:	out	<< "Zoeld";		break;
	case Card::MOCK:	out	<< "Mock";		break;
	case Card::TOECK:	out	<< "Toeck";		break;
	case Card::PIROS:	out	<< "Piros";		break;
	}

	return out;
}

std::ostream& operator<<(std::ostream &out, const Card::CardTyp &typ)
{
	switch (typ)
	{
	case Card::PIROS: out << "Piros"; break;
	case Card::TOECK: out << "Toeck"; break;
	case Card::MOCK: out << "Mock"; break;
	case Card::ZOELD: out << "Zoeld"; break;
	}

	return out;
}

void Card::setPosition(float xPos, float yPos)
{
	m_graphicalCard.setPosition(xPos, yPos);
}

const std::string Card::getCardName() const
{
	std::string temp;
	switch (m_rank)
	{
	case Card::ASS:		temp += "Ace";		break;
	case Card::ZEHN:	temp += "X";			break;
	case Card::NEUN:	temp += "IX";		break;
	case Card::ACHT:	temp += "VIII";		break;
	case Card::SIEBEN:	temp += "VII";		break;
	case Card::KOENIG:	temp += "King";	break;
	case Card::DAME:	temp += "Queen";		break;
	case Card::BUBE:	temp += "Jack";		break;
	}

	temp += " ";

	switch (m_typ)
	{
	case Card::ZOELD:	temp += "Zoeld";			break;
	case Card::MOCK:	temp += "Mock";			break;
	case Card::TOECK:	temp += "Toeck";			break;
	case Card::PIROS:	temp += "Piros";		break;
	}

	return temp;
}