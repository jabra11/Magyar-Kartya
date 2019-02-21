#pragma once
#include <array>
#include "SFML/Graphics.hpp"
#include "Card.h"

extern std::array<std::array<sf::Texture, 8>, 4> textureArr;
extern std::array<sf::Texture, 4> otherTextureArr;

namespace myTextures
{
	enum CardTyp
	{
		Z�LD,
		T�CK,
		MOCK,
		PIROS,
		MAX_TYPES
	};
	enum CardRank
	{
		DAME,
		K�NIG,
		BUBE,
		SIEBEN,
		ACHT,
		NEUN,
		ZEHN,
		ASS,
		MAX_RANKS
	};

	enum OtherTextures
	{
		WUNSCHKARTE_AKTIV_PIROS,
		WUNSCHKARTE_AKTIV_T�CK,
		WUNSCHKARTE_AKTIV_MOCK,
		WUNSCHKARTE_AKTIV_Z�LD,

		WUNSCHKARTE_Z�LD,
		WUNSCHKARTE_T�CK,
		WUNSCHKARTE_MOCK,
		WUNSCHKARTE_PIROS
	};

	void initTextures(std::array<std::array<sf::Texture, 8>, 4> &x, std::array<sf::Texture, 4> &y);
}
