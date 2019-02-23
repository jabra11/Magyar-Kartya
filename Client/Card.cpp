#include "Card.h"


Card::Card(const CardTyp &typ, const CardRank &rank, float xPos, float yPos, bool canBeMoved)
	:m_typ{typ}, m_rank{rank}, m_canBeMoved{canBeMoved}
{
	setTexture();
	m_graphicalCard.scale(0.4f, 0.4f);
	m_graphicalCard.setOrigin(100.0f, 162.8f);
	m_graphicalCard.setPosition(xPos, yPos);
}

const bool Card::getMoveStatus() const
{
	return m_canBeMoved;
}

void Card::changeMoveStatus(bool status)
{
	m_canBeMoved = status;
}

/*const sf::Texture& Card::getTexture() const
{
	return m_graphicalCard.getTexture();
}*/

void Card::setTexture(const sf::Texture &texture)
{
	m_graphicalCard.setTexture(texture);
}

void Card::setTexture()
{
	using namespace myTextures;
	switch (m_typ)
	{
	case Z�LD:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[Z�LD][DAME], true); break;
		case CardRank::K�NIG:	m_graphicalCard.setTexture(textureArr[Z�LD][K�NIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[Z�LD][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[Z�LD][SIEBEN], true); break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[Z�LD][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[Z�LD][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[Z�LD][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[Z�LD][ASS], true); break;
		default:				std::cout << "error in setTexture case ZOELD switch"; break;
		}
		break;
	}

	case T�CK:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[T�CK][DAME], true); break;
		case CardRank::K�NIG:	m_graphicalCard.setTexture(textureArr[T�CK][K�NIG], true); break;
		case CardRank::BUBE:	m_graphicalCard.setTexture(textureArr[T�CK][BUBE], true); break;
		case CardRank::SIEBEN:	m_graphicalCard.setTexture(textureArr[T�CK][SIEBEN], true);  break;
		case CardRank::ACHT:	m_graphicalCard.setTexture(textureArr[T�CK][ACHT], true); break;
		case CardRank::NEUN:	m_graphicalCard.setTexture(textureArr[T�CK][NEUN], true); break;
		case CardRank::ZEHN:	m_graphicalCard.setTexture(textureArr[T�CK][ZEHN], true); break;
		case CardRank::ASS:		m_graphicalCard.setTexture(textureArr[T�CK][ASS], true); break;
		default:				std::cout << "error in setTexture case TOECK switch"; break;
		}
		break;
	}

	case MOCK:
	{
		switch (m_rank)
		{
		case CardRank::DAME:	m_graphicalCard.setTexture(textureArr[MOCK][DAME], true); break;
		case CardRank::K�NIG:	m_graphicalCard.setTexture(textureArr[MOCK][K�NIG], true); break;
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
		case CardRank::K�NIG:	m_graphicalCard.setTexture(textureArr[PIROS][K�NIG], true); break;
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
	case Card::ASS:		out	<< "Ass";		break;
	case Card::ZEHN:	out	<< "X";			break;
	case Card::NEUN:	out	<< "IX";		break;
	case Card::ACHT:	out	<< "VIII";		break;
	case Card::SIEBEN:	out	<< "VII";		break;
	case Card::K�NIG:	out	<< "Koenig";	break;
	case Card::DAME:	out	<< "Dame";		break;
	case Card::BUBE:	out	<< "Bube";		break;
	}

	out << " ";

	switch (card.m_typ)
	{
	case Card::Z�LD:	out	<< "Zoeld";		break;
	case Card::MOCK:	out	<< "Mock";		break;
	case Card::T�CK:	out	<< "Toeck";		break;
	case Card::PIROS:	out	<< "Piros";		break;
	}

	return out;
}

std::ostream& operator<<(std::ostream &out, const Card::CardTyp &typ)
{
	switch (typ)
	{
	case Card::PIROS: out << "Piros"; break;
	case Card::T�CK: out << "Toeck"; break;
	case Card::MOCK: out << "Mock"; break;
	case Card::Z�LD: out << "Zoeld"; break;
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
	case Card::ASS:		temp += "Ass";		break;
	case Card::ZEHN:	temp += "X";			break;
	case Card::NEUN:	temp += "IX";		break;
	case Card::ACHT:	temp += "VIII";		break;
	case Card::SIEBEN:	temp += "VII";		break;
	case Card::K�NIG:	temp += "Koenig";	break;
	case Card::DAME:	temp += "Dame";		break;
	case Card::BUBE:	temp += "Bube";		break;
	}

	temp += " ";

	switch (m_typ)
	{
	case Card::Z�LD:	temp += "Z�ld";			break;
	case Card::MOCK:	temp += "Mock";			break;
	case Card::T�CK:	temp += "T�ck";			break;
	case Card::PIROS:	temp += "Piros";		break;
	}

	return temp;
}