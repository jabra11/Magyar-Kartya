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
#include "ReturnCodes.h"

// macros for keys in unicode

// unicode for backspace
#define BACKSPACE			0x00000008
#define ENTER_ON_WINDOWS	0x0000000D
//////////////////////////////////////


int clientSession(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, OnlinePlayer& player);
int hostSession(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, OnlinePlayer& player, bool is_host);

int multiplayerSetup(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture, const bool is_host)
{
	// do global texture init
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);
	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");

	bool setup_finished{ false };
	int result{ 0 };
	bool play_again{ true };

	constexpr int port{ 55000 };


	sf::Event evnt;
	sf::String player_input{ "192.168.208.106" };

	// initialize text objects to draw with 
	sf::Text player_text;
	player_text.setFont(myFont);
	player_text.setPosition(windowSettings::windowX / 2, windowSettings::windowY / 2);
	player_text.setCharacterSize(50);

	sf::Text enter_the_ip;
	enter_the_ip.setFont(myFont);
	enter_the_ip.setString("Please enter the IPv4-address of your opponent:");
	enter_the_ip.setCharacterSize(50);
	enter_the_ip.setPosition(windowSettings::windowX / 2 - enter_the_ip.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 4);
	
	sf::Text go_back;
	go_back.setFont(myFont);
	go_back.setCharacterSize(40);
	go_back.setString("Go back");
	go_back.setPosition(windowSettings::windowX / 20 * 19 - go_back.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 0);

	sf::Text won_game;
	won_game.setFont(myFont);
	won_game.setCharacterSize(50);
	won_game.setString("You have won the game!");
	won_game.setPosition(windowSettings::windowX / 20 * 10 - won_game.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	sf::Text lost_game;
	lost_game.setFont(myFont);
	lost_game.setCharacterSize(50);
	lost_game.setString("You have lost the game.");
	lost_game.setPosition(windowSettings::windowX / 20 * 10 - lost_game.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	sf::Text play_again_tex;
	play_again_tex.setFont(myFont);
	play_again_tex.setCharacterSize(50);
	play_again_tex.setString("Play again");
	play_again_tex.setPosition(windowSettings::windowX / 20 * 10 - play_again_tex.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 5);

	OnlinePlayer player{ &logic, port};
	

	bool mouse_pressed{ false };
	bool mouse_released{ false };
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

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (go_back.getGlobalBounds().contains(mouse_pos))
					return ReturnCodes::EARLY_EXIT;

				mouse_pressed = true;
				mouse_released = false;
			}

			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				mouse_pressed = false;
				mouse_released = true;
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
				player_text.setString("Waiting for connections...\n");
				player_text.setCharacterSize(50);
				player_text.setPosition(windowSettings::windowX / 2 - player_text.getGlobalBounds().width / 2,
					windowSettings::windowY / 10 * 3);
			}
		}


		if (setup_finished)
		{
			if (play_again)
			{
				if (true)
				{
					// start the host session
					result = hostSession(gameWindow, logic, playTable, player, is_host);

					
					play_again = false;
				}

				/*else
				{
					// start the client session
					result = clientSession(gameWindow, logic, playTable, player);
					play_again = false;
				}*/
			}

			// won the game
			if (result == ReturnCodes::WON)
			{
				if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
					play_again = true;
			}

			// lost the game
			else if (result == ReturnCodes::LOST)
			{
				if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
					play_again = true;
			}


			// clear
			gameWindow.clear();


			// draw
			gameWindow.draw(playTable);
			gameWindow.draw(go_back);
			
			if (result == ReturnCodes::WON)
				gameWindow.draw(won_game);

			else if (result == ReturnCodes::LOST)
				gameWindow.draw(lost_game);

			if (!play_again)
				gameWindow.draw(play_again_tex);


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
			gameWindow.draw(go_back);

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