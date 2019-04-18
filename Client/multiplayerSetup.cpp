#include <iostream>
#include <thread>
#include <array>
#include <chrono>

#include "SFML/Graphics.hpp"

#include "Card.h"
#include "Deck.h"
#include "textureArray.h"
#include "OnlineEnemy.h"
#include "OnlinePlayer.h"
#include "Logic.h"
#include "Client.h"
#include "Host.h"

// macros for keys in unicode

// unicode for backspace
#define BACKSPACE			0x00000008

// unicode for enter
#define ENTER_ON_WINDOWS	0x0000000D
//////////////////////////////////////


int clientSession(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, OnlinePlayer& player);
int hostSession(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, OnlinePlayer& player);

int multiplayerSetup(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture, const bool is_host)
{
	// do global texture init
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);
	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");

	bool setup_finished{ false };
	constexpr int port{ 55000 };


	sf::Event evnt;
	sf::String player_input;

	sf::Text player_text;
	player_text.setFont(myFont);
	player_text.setPosition(windowSettings::windowX / 2, windowSettings::windowY / 2);
	player_text.setCharacterSize(50);

	sf::Text enter_the_ip;
	enter_the_ip.setFont(myFont);
	enter_the_ip.setString("Please enter the IPv4 of your opponent:");
	enter_the_ip.setCharacterSize(50);
	enter_the_ip.setPosition(windowSettings::windowX / 2 - enter_the_ip.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 4);
	

	OnlinePlayer player{ &logic, port};

	while (gameWindow.isOpen())
	{
		sf::Vector2f mouse_pos{ sf::Mouse::getPosition(gameWindow) };


		while (gameWindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{ 
				gameWindow.close();
			}

			
			if (evnt.type == sf::Event::TextEntered)
			{
				if (!is_host && !setup_finished)
				{
					//std::cout << evnt.text.unicode << std::endl;
					if (evnt.text.unicode == BACKSPACE)
					{
						if (player_input.getSize() > 0)
						{
							player_input.erase(player_input.getSize() - 1);
							player_text.setString(player_input);
						}
					}

					else if (evnt.text.unicode == ENTER_ON_WINDOWS)
					{
						if (player_input.getSize() > 0)
						{
							player.m_client.set_IP_address(static_cast<std::string>(player_input));
							if (player.m_client.connect_to_user())
							{
								// worked, great!
								player_input.clear();
								player_text.setString(player_input);

								setup_finished = true;
							}
							else
								//did not work, not great

							player_input.clear();
							player_text.setString(player_input);
						}
					}

					else
					{
						player_input += evnt.text.unicode;
						player_text.setPosition(windowSettings::windowX / 2 - player_text.getGlobalBounds().width / 2,
							windowSettings::windowY / 2);
						player_text.setString(player_input);
					}
				}
			}
			
		}

		if (is_host)
		{
			if (!player.m_host.m_enlisted_thread)
			{
				std::thread t1{ &Host::wait_for_connection, &player.m_host, &player.m_host.m_found_a_connection };
				t1.detach();
				player.m_host.m_enlisted_thread = true;
			}
			

			if (player.m_host.m_found_a_connection)
			{
				player_text.setString("Found a connection.\n");
				player_text.setCharacterSize(50);
				player_text.setPosition(windowSettings::windowX / 2 - player_text.getGlobalBounds().width / 2,
					windowSettings::windowY / 10 * 3);
				setup_finished = true;
			}
			else
			{
				player_text.setString("Waiting for connections.\n");
				player_text.setCharacterSize(50);
				player_text.setPosition(windowSettings::windowX / 2 - player_text.getGlobalBounds().width / 2,
					windowSettings::windowY / 10 * 3);
			}
		}


		if (setup_finished)
		{

			if (is_host)
			{
				// start the host session
				int result{ hostSession(gameWindow, logic, playTable, player) };

			}

			else
			{
				// start the client session
				int result{ clientSession(gameWindow, logic, playTable, player) };
			}

			// clear
			gameWindow.clear();


			// draw
			gameWindow.draw(playTable);


			// display
			gameWindow.display();
		}
			
		


		// draw setup screen
		else
		{
			// clear
			gameWindow.clear();

			// draw

			gameWindow.draw(playTable);
			gameWindow.draw(player_text);

			if (!is_host)
				gameWindow.draw(enter_the_ip);

			// display

			gameWindow.display();
		}
	}

	// preliminary return statement
	return 0;
	// ----------------------------
}