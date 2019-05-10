#include <iostream>
#include <thread>
#include <array>
#include <chrono>

#include "SFML/Graphics.hpp"

#include "headers/Card.h"
#include "headers/Deck.h"
#include "headers/textureArray.h"
#include "headers/OnlineEnemy.h"
#include "headers/OnlinePlayer.h"
#include "headers/Logic.h"
#include "headers/Client.h"
#include "headers/Host.h"
#include "headers/ReturnCodes.h"

// key macros expanding unicodes

#define BACKSPACE			0x00000008
#define ENTER_ON_WINDOWS	0x0000000D
//////////////////////////////////////


int multiplayer(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, Client& client, Host& host, bool is_host);

int multiplayerSetup(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture, const bool is_host,
	int& wins, int& loses)
{
	// do global texture init
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);
	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");

	bool setup_finished{ false };
	int result{ 0 };
	bool play_again{ true };
	constexpr unsigned short port{ unsigned short(55000) };


	sf::Event evnt;
	sf::String player_input{ "192.168.208.106" };

	// initialize text objects to draw with 
	sf::Text player_text{"", myFont, 50};
	player_text.setPosition(windowSettings::windowX / 2, windowSettings::windowY / 2);

	sf::Text enter_the_ip{ "Please enter the IPv4-address of your opponent:", myFont, 50 };
	enter_the_ip.setPosition(windowSettings::windowX / 2 - enter_the_ip.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 4);
	
	sf::Text go_back{ "Go back", myFont, 40 };
	go_back.setPosition(windowSettings::windowX / 20 * 19 - go_back.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 0);

	sf::Text won_game{ "You have won the game!", myFont, 50 };
	won_game.setPosition(windowSettings::windowX / 20 * 10 - won_game.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	sf::Text lost_game{ "You have lost the game.", myFont, 50 };
	lost_game.setPosition(windowSettings::windowX / 20 * 10 - lost_game.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	sf::Text play_again_tex{ "Play again", myFont, 50 };
	play_again_tex.setPosition(windowSettings::windowX / 20 * 10 - play_again_tex.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 5);

	//OnlinePlayer player{ &logic, port};
	Host host{ port, is_host };
	Client client{ port, is_host };
	
	bool has_won{ false };

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
							client.set_IP_address(static_cast<std::string>(player_input));
							if (client.connect_to_user())
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
			if (!host.m_enlisted_thread)
			{
				std::thread t1{ &Host::wait_for_connection, &host, &host.m_found_a_connection };
				t1.detach();
				host.m_enlisted_thread = true;
			}
			

			if (host.m_found_a_connection)
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

				// start the host session
				result = multiplayer(gameWindow, logic, playTable, client, host, is_host);
				mouse_pressed = false;
				play_again = false;

			}

			// won the game
			if (result == ReturnCodes::WON)
			{
				has_won = true;
				++wins;
				if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
					play_again = true;

				result = -1;
			}

			// lost the game
			else if (result == ReturnCodes::LOST)
			{
				has_won = false;
				++loses;
				if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
					play_again = true;

				result = -1;
			}


			// clear
			gameWindow.clear();


			// draw
			gameWindow.draw(playTable);
			gameWindow.draw(go_back);
			
			if (has_won)
				gameWindow.draw(won_game);

			else if (!has_won)
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