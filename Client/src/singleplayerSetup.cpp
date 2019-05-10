#include "SFML/Graphics.hpp"

#include "headers/Logic.h"
#include "headers/ReturnCodes.h"



int singleplayer(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture);

int singleplayer_setup(sf::RenderWindow& gameWindow, Logic& logic, const sf::Texture& playTableTexture,
						int& wins, int& loses)
{
	// Initialize graphics
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);

	sf::Font myFont;
	myFont.loadFromFile("resources/font/testFont.ttf");

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
	//

	bool mouse_pressed{ false };
	bool mouse_released{ false };

	bool play_again{ true };
	int game_result{ -1 };

	bool won{ false };

	sf::Event event;

	std::array<sf::Text, 5> killFeed;

	while (gameWindow.isOpen())
	{
		sf::Vector2f mouse_pos{ sf::Mouse::getPosition(gameWindow) };

		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				gameWindow.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (go_back.getGlobalBounds().contains(mouse_pos))
					return ReturnCodes::EARLY_EXIT;

				mouse_pressed = true;
				mouse_released = false;
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				mouse_pressed = false;
				mouse_released = true;
			}
		}

		if (play_again)
		{
			play_again = false;
			game_result = singleplayer(gameWindow, logic, playTableTexture);
			mouse_pressed = false;
		}

		if (game_result == ReturnCodes::WON)
		{
			game_result = -1;
			won = true;
			++wins;
		}
		else if (game_result == ReturnCodes::LOST)
		{
			game_result = -1;
			won = false;
			++loses;
		}

		if (mouse_pressed && play_again_tex.getGlobalBounds().contains(mouse_pos))
			play_again = true;

		// clear
		gameWindow.clear();

		// draw

		gameWindow.draw(playTable);
		gameWindow.draw(go_back);

		if (won)
			gameWindow.draw(won_game);

		else if (!won)
			gameWindow.draw(lost_game);

		if (!play_again)
			gameWindow.draw(play_again_tex);

		float xOffset{ 0 };
		for (unsigned int i{ 0 }; i < killFeed.size(); ++i)
		{
			//std::cout << logic.getFeedString(i);
			killFeed[i] = sf::Text(logic.getFeedString(i), myFont, 20u);
			killFeed[i].setPosition(10, ((windowSettings::windowY * 0.13) - xOffset));
			xOffset += 25;
			gameWindow.draw(killFeed[i]);
		}

		// display
		gameWindow.display();
	}
}