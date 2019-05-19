#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#define NOMINMAX
#include <UserEnv.h>

#include "headers/textureArray.h"
#include "headers/Logic.h"
#include "headers/windowSettings.h"


void gameMenu(int &gewonnen, int &verloren);
void initializeStats(int&, int&);
void saveStats(int&, int&);
std::string get_userpath();

int main()
{
	//TO-DO
	/*
		- fix design flaw in OnlineUser, Client, Host classes...  (..XD)

		- Deck mischen im Onlinemodus
		- Im Onlinemodus immer auf Reaktion vom Gegner beim Legen eines Buben warten (done)
		- Onlinespiel nur mit selber Anzahl der Startkarten anfangen
		- 
	*/

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

	std::string path{ get_userpath() };
	std::cout << "Initializing stats..\n";
	
	namespace fs = std::experimental::filesystem;

	fs::path dir = path + "/MagyarKartya/stats";

	if (!fs::is_directory(dir) || !fs::exists(dir))
	{
		std::cout << "Did not find the directory, creating now..\n";
		fs::create_directories(dir);
	}

	std::fstream wins;
	wins.open(path + "/MagyarKartya/stats/wins.txt", std::ios::out);

	std::fstream loses;
	loses.open(path + "/MagyarKartya/stats/loses.txt", std::ios::out);


	if (wins.is_open() && loses.is_open())
	{
		wins >> gewonnen;
		wins.close();

		loses >> verloren;
		loses.close();

		std::cout << "Initialized.\n";
	}
	else
	{
		if (!wins.is_open())
			std::cout << "Couldn't open " << path + R"(\MagyarKartya\stats\wins.txt")" << std::endl;
		else
			std::cout << "Couldn't open " << path  + R"(\MagyarKartya\stats\loses.txt")" << std::endl;

		std::cout << "Failed to initialize stats.\n";
	}
}

void saveStats(int& gewonnen, int& verloren)
{
	std::string path{ get_userpath() };

	std::cout << "Saving..\n";

	std::ofstream wins;
	wins.open(path + "/MagyarKartya/stats/wins.txt", std::ostream::out);

	std::ofstream loses;
	loses.open(path + "/MagyarKartya/stats/loses.txt", std::ostream::out);

	if (wins.is_open() && loses.is_open())
	{
		wins << gewonnen;
		wins.close();

		loses << verloren;
		loses.close();

		std::cout << "Saved.\n";
	}
	else
	{
		if (!wins.is_open())
			std::cout << "Couldn't open " << path + R"(\MagyarKartya\stats\wins.txt")" << std::endl;
		else
			std::cout << "Couldn't open " << path + R"(\MagyarKartya\stats\loses.txt")" << std::endl;

		std::cout << "Failed to save.\n";
	}
}

std::string get_userpath()
{
	HANDLE token_handle = nullptr;
	OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token_handle);

	char buffer_string[50];

	LPSTR profile_dir = buffer_string;
	DWORD size = 50;


	GetUserProfileDirectoryA(token_handle, profile_dir, &size);

	return buffer_string;
}