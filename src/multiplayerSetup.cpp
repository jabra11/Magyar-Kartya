#include <iostream>
#include <thread>
#include <array>
#include <chrono>

#include "SFML/Graphics.hpp"

#include "Card.hpp"
#include "Deck.hpp"
#include "textureArray.hpp"
#include "OnlineEnemy.hpp"
#include "OnlinePlayer.hpp"
#include "Logic.hpp"
#include "Client.hpp"
#include "Host.hpp"
#include "ReturnCodes.hpp"

// key macros expanding unicodes

#define BACKSPACE			0x0008
#define ENTER_ON_WINDOWS	0x000D
//////////////////////////////////////


int multiplayer(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, Client& client, Host& host, bool is_host);

int multiplayer_setup(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture, const bool is_host,
	int& wins, int& loses)
{
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);
	sf::Font myFont;
	myFont.loadFromFile("../resources/font/testFont.ttf");

	bool setup_finished{ false };
	int result{ ReturnCodes::PLACEHOLDER };
	bool play_again{ true };
	constexpr unsigned short port{ 55000 };

	// disable cheats in online mode
	logic.m_viewEnemyHand = false;

	sf::Event evnt;
	sf::String player_input{ "LOCALHOST" };

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

	sf::Text lost_connection{ "You have lost the connection", myFont, 50 };
	lost_connection.setPosition(windowSettings::windowX / 20 * 10 - lost_connection.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 4);

	Host host{ port, is_host };
	Client client{ port, is_host };
	
	std::array<sf::Text, 5> killFeed;

	bool has_won{ false };
	bool disconnected{ false };

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
								player_input.clear();
								player_text.setString(player_input);

								sf::Packet temp;
								if (client.m_socket.receive(temp) == sf::Socket::Done)
								{
									temp >> logic.m_sizeOfStartHand;
									setup_finished = true;
								}
							}

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
				host.m_found_a_connection = false;

				player_text.setString("Found a connection.\n");
				player_text.setCharacterSize(50);
				player_text.setPosition(windowSettings::windowX / 2 - player_text.getGlobalBounds().width / 2,
					windowSettings::windowY / 10 * 3);

				sf::Packet temp;
				temp << logic.m_sizeOfStartHand;
				if (host.m_socket.send(temp) == sf::Socket::Done)
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
				play_again = false;
				// start the host session
				result = multiplayer(gameWindow, logic, playTable, client, host, is_host);
				mouse_pressed = false;
			}

			// won the game
			if (result == ReturnCodes::WON)
			{
				has_won = true;
				++wins;

				result = ReturnCodes::PLACEHOLDER;
			}
			// lost the game
			else if (result == ReturnCodes::LOST)
			{
				has_won = false;
				++loses;

				result = ReturnCodes::PLACEHOLDER;
			}

			// lost connection
			if (result == ReturnCodes::LOST_CONNECTION)
			{
				disconnected = true;
				setup_finished = false;

				result = ReturnCodes::PLACEHOLDER;
			}

			if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
				play_again = true;

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

			float xOffset{ 0 };
			for (unsigned int i{ 0 }; i < killFeed.size(); ++i)
			{
				killFeed[i] = sf::Text(logic.getFeedString(i), myFont, 20u);
				killFeed[i].setPosition(10, ((windowSettings::windowY * 0.13) - xOffset));
				xOffset += 25;
				gameWindow.draw(killFeed[i]);
			}

			// display
			gameWindow.display();
		}
		else if (disconnected)
		{
			gameWindow.clear();

			gameWindow.draw(playTable);
			gameWindow.draw(lost_connection);
			gameWindow.draw(go_back);

			if (mouse_pressed && go_back.getGlobalBounds().contains(mouse_pos))
				return ReturnCodes::EXIT;

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