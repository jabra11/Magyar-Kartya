#include "SFML/Graphics.hpp"	
#include "headers/windowSettings.h"
#include <iostream>
#include "headers/Logic.h"
#include "headers/ReturnCodes.h"

int singleplayer_setup(sf::RenderWindow& renderWindow, Logic& logic, const sf::Texture& playTableTexture,
	int& wins, int& loses);
int multiplayerSetup(sf::RenderWindow& renderWindow, Logic &logic, const sf::Texture &playTableTexture, const bool host,
	int& wins, int& loses);

void gameMenu(int& gewonnen, int& verloren)
{
	sf::RenderWindow gameWindow(sf::VideoMode(windowSettings::windowX, windowSettings::windowY), "Magyar Kartya", sf::Style::Close);

	sf::Image icon;
	if (icon.loadFromFile("resources/images/icon.jpg"))
		gameWindow.setIcon(32, 32, icon.getPixelsPtr());

	// will move this somewhere else later
	gameWindow.setFramerateLimit(600);

	//gameWindow.setVerticalSyncEnabled(true);


	sf::Texture menu; 
	menu.loadFromFile("resources/images/greyBackground.jpg");



	sf::Texture playTableGrey; playTableGrey.loadFromFile("resources/images/greyBackground.jpg");
	sf::Texture playTableGreen; playTableGreen.loadFromFile("resources/images/playTable.png");

	sf::Texture textureToPass = playTableGrey;

	sf::RectangleShape test{ sf::Vector2f(200.0f, 200.0f) };

	Logic logic;

	//  defining the font for the text object/s
	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");
	//

	// defining the text objects
	sf::Text play{"Spielen", myFont, 90u };
	play.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (play.getGlobalBounds().width / 2.0f), windowSettings::windowY / 20 * 2.0f));

	sf::Text multiplayerText{ "Multiplayer", myFont, 90u };
	multiplayerText.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (multiplayerText.getGlobalBounds().width / 2.0f), windowSettings::windowY / 20 * 5.0f));

	sf::Text options{ "Optionen", myFont, 90u };
	options.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (options.getGlobalBounds().width / 2.0f), windowSettings::windowY / 20 * 8.0f));

	sf::Text stats{ "Statistiken", myFont, 90u };
	stats.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (stats.getGlobalBounds().width / 2.0f), windowSettings::windowY / 20 * 11.0f));

	sf::Text exit{ "Exit", myFont, 90u };
	exit.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (exit.getGlobalBounds().width / 2.0f), windowSettings::windowY / 20 * 15.0f));

	// stats
	//

	bool showStats{ false };
	bool showOptions{ false };

	bool host{ true };

	int tableTex{ 1 };


	while (gameWindow.isOpen())
	{
		bool mouseLeftPressed{ false };
		//bool mouseRightPressed{ false };

		bool mouseLeftReleased{ false };
		//bool mouseRightReleased{ false };
		

		sf::Event evnt;
		sf::Vector2f mousePos{ sf::Mouse::getPosition(gameWindow) };

		while (gameWindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				gameWindow.close();
				return;
			}

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mouseLeftPressed = true;
					mouseLeftReleased = false;
				}
			}

			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mouseLeftReleased = true;
					mouseLeftPressed = false;
				}
			}
		}

		if (mouseLeftPressed && !mouseLeftReleased)
		{
			// SINGLEPLAYER
			if (play.getGlobalBounds().contains(mousePos) && !showStats && !showOptions)
			{
				singleplayer_setup(gameWindow, logic, textureToPass, gewonnen, verloren);
			}

			// MULTIPLAYER
			if (multiplayerText.getGlobalBounds().contains(mousePos) && !showStats && !showOptions)
			{

				int gameStatus{ multiplayerSetup(gameWindow, logic, textureToPass, host, gewonnen, verloren) };

				/*if (gameStatus == ReturnCodes::WON)
					++verloren;

				else if (gameStatus == ReturnCodes::LOST)
					++gewonnen;

				else if (gameStatus == ReturnCodes::EARLY_EXIT)
				{
					// do nothing
				}
				/*else
					return;*/
			}

			if (stats.getGlobalBounds().contains(mousePos) && !showOptions)
			{
				showStats = true;
			}

			if (options.getGlobalBounds().contains(mousePos) && !showStats)
			{
				showOptions = true;
			}

			if (exit.getGlobalBounds().contains(mousePos) && !showStats && !showOptions)
			{
				return;
			}
		}

		if (showStats)
		{
			sf::Text gewonnenText{ "Gewonnen: " + std::to_string(gewonnen), myFont, 80u };
			gewonnenText.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (gewonnenText.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 1.0f));

			sf::Text verlorenText{ "Verloren: " + std::to_string(verloren), myFont, 80u };
			verlorenText.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (verlorenText.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 2.0f));

			sf::Text bilanzText{ "Bilanz: " + std::to_string((gewonnen - verloren)), myFont, 80u };
			bilanzText.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (bilanzText.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 3.0f));

			sf::Text resetStats{ "Zurücksetzen", myFont, 80u };
			resetStats.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (resetStats.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 7.0f));

			sf::Text goBack{ "Zurück", myFont, 80u };
			goBack.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (goBack.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 8.0f));

			if (mouseLeftPressed && !mouseLeftReleased)
			{
				if (resetStats.getGlobalBounds().contains(mousePos))
				{
					gewonnen = 0;
					verloren = 0;
				}

				if (goBack.getGlobalBounds().contains(mousePos))
					showStats = false;
			}

			gameWindow.clear();

			gameWindow.draw(sf::Sprite(menu));
			gameWindow.draw(gewonnenText);
			gameWindow.draw(verlorenText);
			gameWindow.draw(bilanzText);
			gameWindow.draw(resetStats);
			gameWindow.draw(goBack);
			gameWindow.display();
		}

		else if (showOptions)
		{
			sf::Text startSize{ "Startkarten: " + std::to_string(logic.m_sizeOfStartHand), myFont, 50u };
			startSize.setPosition(windowSettings::windowX / 10 * 1.0f, windowSettings::windowY / 10 * 2.0f);

			std::string viewEnemyHand{ "" };
			(logic.m_viewEnemyHand) ? viewEnemyHand = "Ja" : viewEnemyHand = "Nein";
			sf::Text showEnemyHand{ "Zeige Gegnerkarten: " + viewEnemyHand, myFont, 50u };
			showEnemyHand.setPosition(windowSettings::windowX / 10 * 1.0f, windowSettings::windowY / 10 * 3.0f);


			std::string tableTexString{ "" };
			(tableTex) ? tableTexString = "Grau" : tableTexString = "Gruen";
			sf::Text chooseTableTex{ "Spielhintergrund: " + tableTexString, myFont, 50u };
			chooseTableTex.setPosition(windowSettings::windowX / 10 * 1.0f, windowSettings::windowY / 10 * 4.0f);

			std::string onlineHost{ "" };
			(host) ? onlineHost = "Host" : onlineHost = "Client";
			sf::Text onlineHostTex{ "Onlinemodus: " + onlineHost, myFont, 50u };
			onlineHostTex.setPosition(windowSettings::windowX / 10 * 1.0f, windowSettings::windowY / 10 * 5.0f);

			sf::Text goBack{ "Zurueck", myFont, 80u };
			goBack.setPosition(sf::Vector2f((windowSettings::windowX / 2.0f) - (goBack.getGlobalBounds().width / 2.0f), windowSettings::windowY / 10 * 8.0f));

			if (mouseLeftPressed && !mouseLeftReleased)
			{
				if (startSize.getGlobalBounds().contains(mousePos))
				{
					if (logic.m_sizeOfStartHand == 5)
						logic.m_sizeOfStartHand = 10;

					else
						logic.m_sizeOfStartHand = 5;
				}

				if (showEnemyHand.getGlobalBounds().contains(mousePos))
					(logic.m_viewEnemyHand) ? logic.m_viewEnemyHand = false : logic.m_viewEnemyHand = true;

				if (chooseTableTex.getGlobalBounds().contains(mousePos))
				{
					if (tableTex == 1)
					{
						tableTex = 0;
						textureToPass = playTableGreen; 
					}
					else
					{
						tableTex = 1;
						textureToPass = playTableGrey;
					}
				}

				if (onlineHostTex.getGlobalBounds().contains(mousePos))
					(host) ? host = false : host = true;

				if (goBack.getGlobalBounds().contains(mousePos))
					showOptions = false;


			}


			gameWindow.clear();

			gameWindow.draw(sf::Sprite(menu));
			gameWindow.draw(startSize);
			gameWindow.draw(showEnemyHand);
			gameWindow.draw(chooseTableTex);
			gameWindow.draw(onlineHostTex);
			gameWindow.draw(goBack);

			gameWindow.display();
		}

		else
		{
			// clear // 
			gameWindow.clear();

			// drawing // 
			gameWindow.draw(sf::Sprite(menu));
			gameWindow.draw(play);
			gameWindow.draw(multiplayerText);
			gameWindow.draw(options);
			gameWindow.draw(stats);
			gameWindow.draw(exit);


			// display //
			gameWindow.display();
		}
	}
}