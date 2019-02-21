#include <array>
#include "SFML/Graphics.hpp"
#include "textureArray.h"

using namespace myTextures;

std::array<std::array<sf::Texture, 8>, 4> textureArr;
std::array<sf::Texture, 4> otherTextureArr;

void myTextures::initTextures(std::array<std::array<sf::Texture, 8>, 4> &x, std::array<sf::Texture, 4> &y)
{
	x[ZÖLD][DAME].loadFromFile("resources/images/zöld/dame.jpg");
	x[ZÖLD][KÖNIG].loadFromFile("resources/images/zöld/könig.jpg");
	x[ZÖLD][BUBE].loadFromFile("resources/images/zöld/zöld2.jpg");
	x[ZÖLD][SIEBEN].loadFromFile("resources/images/zöld/zöld7.jpg");
	x[ZÖLD][ACHT].loadFromFile("resources/images/zöld/zöld8.jpg");
	x[ZÖLD][NEUN].loadFromFile("resources/images/zöld/zöld9.jpg");
	x[ZÖLD][ZEHN].loadFromFile("resources/images/zöld/zöld10.jpg");
	x[ZÖLD][ASS].loadFromFile("resources/images/zöld/springer.jpg");

	x[TÖCK][DAME].loadFromFile("resources/images/töck/dame.jpg");
	x[TÖCK][KÖNIG].loadFromFile("resources/images/töck/könig.jpg");
	x[TÖCK][BUBE].loadFromFile("resources/images/töck/töck2.jpg");
	x[TÖCK][SIEBEN].loadFromFile("resources/images/töck/töck7.jpg");
	x[TÖCK][ACHT].loadFromFile("resources/images/töck/töck8.jpg");
	x[TÖCK][NEUN].loadFromFile("resources/images/töck/töck9.jpg");
	x[TÖCK][ZEHN].loadFromFile("resources/images/töck/töck10.jpg");
	x[TÖCK][ASS].loadFromFile("resources/images/töck/springer.jpg");

	x[MOCK][DAME].loadFromFile("resources/images/mock/dame.jpg");
	x[MOCK][KÖNIG].loadFromFile("resources/images/mock/könig.jpg");
	x[MOCK][BUBE].loadFromFile("resources/images/mock/mock2.jpg");
	x[MOCK][SIEBEN].loadFromFile("resources/images/mock/mock7.jpg");
	x[MOCK][ACHT].loadFromFile("resources/images/mock/mock8.jpg");
	x[MOCK][NEUN].loadFromFile("resources/images/mock/mock9.jpg");
	x[MOCK][ZEHN].loadFromFile("resources/images/mock/mock10.jpg");
	x[MOCK][ASS].loadFromFile("resources/images/mock/springer.jpg");

	x[PIROS][DAME].loadFromFile("resources/images/piros/dame.jpg");
	x[PIROS][KÖNIG].loadFromFile("resources/images/piros/könig.jpg");
	x[PIROS][BUBE].loadFromFile("resources/images/piros/piros2.jpg");
	x[PIROS][SIEBEN].loadFromFile("resources/images/piros/piros7.jpg");
	x[PIROS][ACHT].loadFromFile("resources/images/piros/piros8.jpg");
	x[PIROS][NEUN].loadFromFile("resources/images/piros/piros9.jpg");
	x[PIROS][ZEHN].loadFromFile("resources/images/piros/piros10.jpg");
	x[PIROS][ASS].loadFromFile("resources/images/piros/springer.jpg");

	y[WUNSCHKARTE_AKTIV_MOCK].loadFromFile("resources/images/mock/mock.jpg");
	y[WUNSCHKARTE_AKTIV_ZÖLD].loadFromFile("resources/images/zöld/zöld.jpg");
	y[WUNSCHKARTE_AKTIV_TÖCK].loadFromFile("resources/images/töck/töck.jpg");
	y[WUNSCHKARTE_AKTIV_PIROS].loadFromFile("resources/images/piros/piros.jpg");
}

