#include <array>
#include "SFML/Graphics.hpp"
#include "textureArray.h"

using namespace myTextures;

std::array<std::array<sf::Texture, 8>, 4> textureArr;
std::array<sf::Texture, 4> otherTextureArr;

void myTextures::initTextures(std::array<std::array<sf::Texture, 8>, 4> &x, std::array<sf::Texture, 4> &y)
{
	x[ZOELD][DAME].loadFromFile("resources/images/zoeld/dame.jpg");
	x[ZOELD][KOENIG].loadFromFile("resources/images/zoeld/koenig.jpg");
	x[ZOELD][BUBE].loadFromFile("resources/images/zoeld/2.jpg");
	x[ZOELD][SIEBEN].loadFromFile("resources/images/zoeld/7.jpg");
	x[ZOELD][ACHT].loadFromFile("resources/images/zoeld/8.jpg");
	x[ZOELD][NEUN].loadFromFile("resources/images/zoeld/9.jpg");
	x[ZOELD][ZEHN].loadFromFile("resources/images/zoeld/10.jpg");
	x[ZOELD][ASS].loadFromFile("resources/images/zoeld/springer.jpg");

	x[TOECK][DAME].loadFromFile("resources/images/toeck/dame.jpg");
	x[TOECK][KOENIG].loadFromFile("resources/images/toeck/koenig.jpg");
	x[TOECK][BUBE].loadFromFile("resources/images/toeck/2.jpg");
	x[TOECK][SIEBEN].loadFromFile("resources/images/toeck/7.jpg");
	x[TOECK][ACHT].loadFromFile("resources/images/toeck/8.jpg");
	x[TOECK][NEUN].loadFromFile("resources/images/toeck/9.jpg");
	x[TOECK][ZEHN].loadFromFile("resources/images/toeck/10.jpg");
	x[TOECK][ASS].loadFromFile("resources/images/toeck/springer.jpg");

	x[MOCK][DAME].loadFromFile("resources/images/mock/dame.jpg");
	x[MOCK][KOENIG].loadFromFile("resources/images/mock/koenig.jpg");
	x[MOCK][BUBE].loadFromFile("resources/images/mock/2.jpg");
	x[MOCK][SIEBEN].loadFromFile("resources/images/mock/7.jpg");
	x[MOCK][ACHT].loadFromFile("resources/images/mock/8.jpg");
	x[MOCK][NEUN].loadFromFile("resources/images/mock/9.jpg");
	x[MOCK][ZEHN].loadFromFile("resources/images/mock/10.jpg");
	x[MOCK][ASS].loadFromFile("resources/images/mock/springer.jpg");

	x[PIROS][DAME].loadFromFile("resources/images/piros/dame.jpg");
	x[PIROS][KOENIG].loadFromFile("resources/images/piros/koenig.jpg");
	x[PIROS][BUBE].loadFromFile("resources/images/piros/2.jpg");
	x[PIROS][SIEBEN].loadFromFile("resources/images/piros/7.jpg");
	x[PIROS][ACHT].loadFromFile("resources/images/piros/8.jpg");
	x[PIROS][NEUN].loadFromFile("resources/images/piros/9.jpg");
	x[PIROS][ZEHN].loadFromFile("resources/images/piros/10.jpg");
	x[PIROS][ASS].loadFromFile("resources/images/piros/springer.jpg");

	y[WUNSCHKARTE_AKTIV_MOCK].loadFromFile("resources/images/mock/mock.jpg");
	y[WUNSCHKARTE_AKTIV_ZOELD].loadFromFile("resources/images/zoeld/zoeld.jpg");
	y[WUNSCHKARTE_AKTIV_TOECK].loadFromFile("resources/images/toeck/toeck.jpg");
	y[WUNSCHKARTE_AKTIV_PIROS].loadFromFile("resources/images/piros/piros.jpg");
}

