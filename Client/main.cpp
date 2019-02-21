#include "textureArray.h"
#include <iostream>
#include <fstream>
#include "windowSettings.h"
#include "Logic.h"

int gameMenu(int &gewonnen, int &verloren);

int main()
{
	int gewonnen{ 0 };
	int verloren{ 0 };

	std::ifstream inputWins;
	inputWins.open("resources/stats/wins.txt");
	inputWins >> gewonnen;
	inputWins.close();

	std::ifstream inputLoses;
	inputLoses.open("resources/loses.txt");
	inputLoses >> verloren;
	inputLoses.close();

	myTextures::initTextures(textureArr, otherTextureArr);
	gameMenu(gewonnen, verloren);

	std::ofstream outputWins;
	outputWins.open("resources/stats/wins.txt");
	outputWins << gewonnen;
	outputWins.close();

	std::ofstream outputLoses;
	outputLoses.open("resources/stats/loses.txt");
	outputLoses << verloren;
	outputLoses.close();

	std::cout << "Tschuess!\n";

	return 0;
}
