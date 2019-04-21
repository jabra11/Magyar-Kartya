#include "textureArray.h"
#include <iostream>
#include <fstream>
#include "windowSettings.h"
#include "Logic.h"

void gameMenu(int &gewonnen, int &verloren);
void initializeStats(int&, int&);
void saveStats(int&, int&);


int main()
{
	int gewonnen{ 0 };
	int verloren{ 0 };

	// read stats from .txt files into variables
	initializeStats(gewonnen, verloren);

	myTextures::initTextures(textureArr, otherTextureArr);
	gameMenu(gewonnen, verloren);

	//read variables into .txt files
	saveStats(gewonnen, verloren);

	std::cout << "Tschuess!\n";

	return 0;
}


void initializeStats(int& gewonnen, int& verloren)
{
	std::ifstream inputWins;
	inputWins.open("resources/stats/wins.txt");
	inputWins >> gewonnen;
	inputWins.close();

	std::ifstream inputLoses;
	inputLoses.open("resources/loses.txt");
	inputLoses >> verloren;
	inputLoses.close();
}

void saveStats(int& gewonnen, int& verloren)
{
	std::ofstream outputWins;
	outputWins.open("resources/stats/wins.txt");
	outputWins << gewonnen;
	outputWins.close();

	std::ofstream outputLoses;
	outputLoses.open("resources/stats/loses.txt");
	outputLoses << verloren;
	outputLoses.close();
}