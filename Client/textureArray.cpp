#include <array>
#include "SFML/Graphics.hpp"
#include "textureArray.h"

using namespace myTextures;

std::array<std::array<sf::Texture, 8>, 4> textureArr;
std::array<sf::Texture, 4> otherTextureArr;

void myTextures::initTextures(std::array<std::array<sf::Texture, 8>, 4> &x, std::array<sf::Texture, 4> &y)
{
	x[Z�LD][DAME].loadFromFile("resources/images/z�ld/dame.jpg");
	x[Z�LD][K�NIG].loadFromFile("resources/images/z�ld/k�nig.jpg");
	x[Z�LD][BUBE].loadFromFile("resources/images/z�ld/z�ld2.jpg");
	x[Z�LD][SIEBEN].loadFromFile("resources/images/z�ld/z�ld7.jpg");
	x[Z�LD][ACHT].loadFromFile("resources/images/z�ld/z�ld8.jpg");
	x[Z�LD][NEUN].loadFromFile("resources/images/z�ld/z�ld9.jpg");
	x[Z�LD][ZEHN].loadFromFile("resources/images/z�ld/z�ld10.jpg");
	x[Z�LD][ASS].loadFromFile("resources/images/z�ld/springer.jpg");

	x[T�CK][DAME].loadFromFile("resources/images/t�ck/dame.jpg");
	x[T�CK][K�NIG].loadFromFile("resources/images/t�ck/k�nig.jpg");
	x[T�CK][BUBE].loadFromFile("resources/images/t�ck/t�ck2.jpg");
	x[T�CK][SIEBEN].loadFromFile("resources/images/t�ck/t�ck7.jpg");
	x[T�CK][ACHT].loadFromFile("resources/images/t�ck/t�ck8.jpg");
	x[T�CK][NEUN].loadFromFile("resources/images/t�ck/t�ck9.jpg");
	x[T�CK][ZEHN].loadFromFile("resources/images/t�ck/t�ck10.jpg");
	x[T�CK][ASS].loadFromFile("resources/images/t�ck/springer.jpg");

	x[MOCK][DAME].loadFromFile("resources/images/mock/dame.jpg");
	x[MOCK][K�NIG].loadFromFile("resources/images/mock/k�nig.jpg");
	x[MOCK][BUBE].loadFromFile("resources/images/mock/mock2.jpg");
	x[MOCK][SIEBEN].loadFromFile("resources/images/mock/mock7.jpg");
	x[MOCK][ACHT].loadFromFile("resources/images/mock/mock8.jpg");
	x[MOCK][NEUN].loadFromFile("resources/images/mock/mock9.jpg");
	x[MOCK][ZEHN].loadFromFile("resources/images/mock/mock10.jpg");
	x[MOCK][ASS].loadFromFile("resources/images/mock/springer.jpg");

	x[PIROS][DAME].loadFromFile("resources/images/piros/dame.jpg");
	x[PIROS][K�NIG].loadFromFile("resources/images/piros/k�nig.jpg");
	x[PIROS][BUBE].loadFromFile("resources/images/piros/piros2.jpg");
	x[PIROS][SIEBEN].loadFromFile("resources/images/piros/piros7.jpg");
	x[PIROS][ACHT].loadFromFile("resources/images/piros/piros8.jpg");
	x[PIROS][NEUN].loadFromFile("resources/images/piros/piros9.jpg");
	x[PIROS][ZEHN].loadFromFile("resources/images/piros/piros10.jpg");
	x[PIROS][ASS].loadFromFile("resources/images/piros/springer.jpg");

	y[WUNSCHKARTE_AKTIV_MOCK].loadFromFile("resources/images/mock/mock.jpg");
	y[WUNSCHKARTE_AKTIV_Z�LD].loadFromFile("resources/images/z�ld/z�ld.jpg");
	y[WUNSCHKARTE_AKTIV_T�CK].loadFromFile("resources/images/t�ck/t�ck.jpg");
	y[WUNSCHKARTE_AKTIV_PIROS].loadFromFile("resources/images/piros/piros.jpg");
}

