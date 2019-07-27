#pragma once
#include <array>
#include "SFML/Graphics.hpp"
#include "Card.hpp"

extern std::array<std::array<sf::Texture, 8>, 4> textureArr;
extern std::array<sf::Texture, 4> otherTextureArr;

namespace myTextures
{
	enum CardTyp
	{
		ZOELD,
		TOECK,
		MOCK,
		PIROS,
		MAX_TYPES
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
		MAX_RANKS
	};

	enum OtherTextures
	{
		WUNSCHKARTE_AKTIV_PIROS,
		WUNSCHKARTE_AKTIV_TOECK,
		WUNSCHKARTE_AKTIV_MOCK,
		WUNSCHKARTE_AKTIV_ZOELD,

		WUNSCHKARTE_ZOELD,
		WUNSCHKARTE_TOECK,
		WUNSCHKARTE_MOCK,
		WUNSCHKARTE_PIROS
	};

	void initTextures(std::array<std::array<sf::Texture, 8>, 4> &x, std::array<sf::Texture, 4> &y);
}
