#include <array>
#include <cassert>
#include <string>
#include <vector>
#include <thread>

#include <SFML/Graphics.hpp>

#include "Logic.hpp"
#include "OnlinePlayer.hpp"
#include "OnlineEnemy.hpp"
#include "TextureHandler.hpp"
#include "Card.hpp"
#include "ReturnCodes.hpp"

int multiplayer(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, Client& client, Host& host, const bool is_hosting = true)
{
	// init rückseiten array
	auto rueckseiten = std::array<sf::Texture, 4>{};
	TextureHandler::init_backcard(rueckseiten);

	// init wish card array
	auto choose_wish_card_sprites = std::array<Card, 4>{};
	TextureHandler::init_wish_card_sprites(choose_wish_card_sprites);

	// init backcard
	sf::Sprite back_card;
	TextureHandler::init_backcard_sprite(back_card);

	// init font
	sf::Font my_font;
	TextureHandler::init_font(my_font);

	sf::Text turn_info{ "Your turnX", my_font, 25 };
	turn_info.setPosition(windowSettings::windowX / 20 * 1 - turn_info.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	// init additional_info_text
	sf::Text additional_info_text;
	additional_info_text.setString("You have to draw XX cards\n");
	additional_info_text.setCharacterSize(40);
	additional_info_text.setFont(my_font);
	additional_info_text.setPosition(windowSettings::windowX / 2 - additional_info_text.getGlobalBounds().width / 2,
		windowSettings::windowY * 0.25f);

	auto additional_info = std::string{ "" };
	bool choose_wishcard{ false };

	Deck deck;

	if (is_hosting)
		deck.set_online_status(true, &host);
	else
		deck.set_online_status(false, nullptr ,&client);

	auto card_stack = std::vector<Card>{};

	constexpr unsigned short port{ 55000u };

	OnlineEnemy enemy{ &host, &client, &logic, &deck, &card_stack, true };

	OnlinePlayer player{&logic, client, host };

	sf::Socket::Status error_flag{ sf::Socket::Status::NotReady };

	// check if a thread has been enlisted to retrieve the packets
	bool thread_has_been_enlisted{ false };

	// check if the thread has finished its work
	bool thread_is_ready{ false };

	// store the retrieved informations
	OnlineUser::Default_packet* enemys_move{ nullptr };

	if (is_hosting)
	{
		enemy.m_is_hosting = true;
		player.set_host_status(true);
	}
	else
	{
		enemy.m_is_hosting = false;
		player.set_host_status(false);
	}

	logic.resetFeed();
	logic.resetStatuses();

	if (is_hosting)
		player.m_host.send_deck_information(deck);
	else
	{
		if (!player.m_client.receive_deck_information(deck))
			return ReturnCodes::LOST_CONNECTION;
	}

	card_stack.push_back(deck.dealCard());

	bool mouse_left_pressed{ false };
	bool mouse_left_released{ false };

	if (is_hosting)
	{
		switch (card_stack.back().getRank())
		{
		case Card::SIEBEN:	logic.m_startWunschKarteAktiv = true;								break;
		case Card::ASS:		logic.m_enemySkips = true;											break;
		case Card::BUBE:	logic.m_enemyHasToDraw = true;	logic.m_amountOfCardsToDraw += 2;	break;
		}

		// init playerhand
		for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i)
		{
			player.drawCard(deck.dealCard(sf::Vector2f{ (windowSettings::windowX / (logic.m_sizeOfStartHand - 2)) + player.m_xOffset, windowSettings::windowY * 0.8f }, card_stack));
			player.m_xOffset += 100;
		}

		// init enemyhand
		for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i)
		{
			if (i % 2 == 0)
				enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, card_stack));
			else
				enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, card_stack));

			enemy.m_xOffset += 50;
		}
	}
	else
	{
		switch (card_stack.back().getRank())
		{
		case Card::SIEBEN:	logic.m_startWunschKarteAktiv = true;								break;
		case Card::ASS:		logic.m_playerSkips = true;											break;
		case Card::BUBE:	logic.m_playerHasToDraw = true;	logic.m_amountOfCardsToDraw += 2;	break;
		}


		// init enemyhand
		for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i)
		{
			if (i % 2 == 0)
				enemy.drawCard(deck.dealCard(sf::Vector2f{windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, card_stack));
			else
				enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, card_stack));

			enemy.m_xOffset += 50;
		}

		// init playerhand
		for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i)
		{
			player.drawCard(deck.dealCard(sf::Vector2f{ (windowSettings::windowX / (logic.m_sizeOfStartHand - 2))
				+ player.m_xOffset, windowSettings::windowY * 0.8f }, card_stack));
			player.m_xOffset += 100;
		}
	}

	std::cout << "Start card: " << card_stack.back() << '\n';

	if (is_hosting)
	{
		// in the host session, the enemy is the first to play
		logic.m_playersTurn = false;
		logic.m_enemysTurn = true;
	}
	else
	{
		// in the client session, the player is the first to play
		logic.m_playersTurn = true;
		logic.m_enemysTurn = false;
	}

	while (gameWindow.isOpen())
	{
		sf::Event evnt;
		sf::Vector2f card_stack_pos{ card_stack.back().getGraphicalCard().getPosition() };
		sf::Vector2f mouse_pos{ sf::Mouse::getPosition(gameWindow) };
		std::string wrong_card_string;
		bool wrong_card{ false };

		while (gameWindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				gameWindow.close();
				return ReturnCodes::EARLY_EXIT;
			}

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mouse_left_pressed = true;
					mouse_left_released = false;
					//std::cout << "MOUSEBUTTON PRESSED\n";
				}
			}
			if (evnt.type == sf::Event::MouseButtonReleased)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mouse_left_released = true;
					mouse_left_pressed = false;
					//std::cout << "mousebutton released\n";
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		for (int i{ 0 }; i < 1; ++i) // player loop
		{
			//if (logic.m_playersTurn) std::cout << "your turn m8\n";
			if (logic.playerSkips() && logic.m_playersTurn)
			{
				logic.m_playersTurn = false;
				logic.m_playerSkips = false;
				std::cout << "You have to skip a round.\n";
				logic.m_enemysTurn = true;
				mouse_left_pressed = false;
				mouse_left_released = true;

				if (is_hosting)
					player.m_host.modify_buffer().is_valid = true;
				else
					player.m_client.modify_buffer().is_valid = true;
				continue;
			}

			if (logic.m_playerHasToDraw && logic.m_playersTurn)
			{
				bool has_draw_cards{ false };
				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (player.getCard(i).getRank() == Card::BUBE)
					{
						has_draw_cards = true;
						break;
					}
				}

				if (has_draw_cards)
					additional_info = "You have to draw " + std::to_string(logic.m_amountOfCardsToDraw) + " cards or strike back!";
				else
					additional_info = "You have to draw " + std::to_string(logic.m_amountOfCardsToDraw) + " cards!";

				additional_info_text.setString(additional_info);
				additional_info_text.setPosition(windowSettings::windowX / 2 - additional_info_text.getGlobalBounds().width / 2,
					windowSettings::windowY* 0.25f);
		

				if (back_card.getGlobalBounds().contains(mouse_pos) && mouse_left_pressed == true && mouse_left_released == false)
				{
					for (int i{ 0 }; i < logic.m_amountOfCardsToDraw; ++i)
						player.drawCard(deck.dealCard(player.getCoord(mouse_left_pressed), card_stack),
							logic.m_amountOfCardsToDraw);

					logic.m_playerHasToDraw = false;
					logic.m_amountOfCardsToDraw = 0;
					logic.m_enemysTurn = true;
					logic.m_playersTurn = false;

					if (is_hosting)
						player.m_host.send_choice_information();
					else
						player.m_client.send_choice_information();

					continue;
				}
			}

			if (mouse_left_pressed && !mouse_left_released)
			{
				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (player.getCard(i).m_graphicalCard.getGlobalBounds().contains(mouse_pos))
					{
						player.move_card(mouse_pos, i);
						break;
					}
				}

				if (choose_wishcard)
				{
					for (size_t i{ 0 }; i < choose_wish_card_sprites.size(); ++i)
					{
						if (choose_wish_card_sprites[i].getGraphicalCard().getGlobalBounds().contains(mouse_pos))
						{
							logic.m_wunschkarte.setTyp(choose_wish_card_sprites[i].getTyp());
							logic.m_wunschkarteAktiv = true;

							// modify the buffer to account for the wishcard_value
							if (is_hosting)
							{
								player.m_host.modify_buffer().wishcard_value = choose_wish_card_sprites[i].getTyp();
								player.m_host.modify_buffer().is_valid = true;
							}
							else
							{
								player.m_client.modify_buffer().wishcard_value = choose_wish_card_sprites[i].getTyp();
								player.m_client.modify_buffer().is_valid = true;
							}

							logic.m_enemysTurn = true;
							logic.m_playersTurn = false;
							choose_wishcard = false;
							std::cout << "You want " << logic.m_wunschkarte.getTyp() << ".\n";

							if (is_hosting)
								player.m_host.send_choice_information();
							else
								player.m_client.send_choice_information();

							if (player.getHandSize() == 0)
								return ReturnCodes::WON;
						}

						// skip unnessesary iterations
						if (!choose_wishcard)
							break;
					}
					// if wishcard has been chosen, skip the rest of the player iteration
					if (!choose_wishcard)
						continue;
				}

				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (card_stack.back().getGraphicalCard().getGlobalBounds()
						.contains(player.getCard(i).getGraphicalCard().getPosition()) && logic.m_playersTurn)
					{
						if (logic.validateMove(player.getCard(i), card_stack.back(), true, logic.m_playerHasToDraw))
						{
							//choose_wishcard = false;
							logic.m_startWunschKarteAktiv = false;
							logic.m_wunschkarteAktiv = false;
							logic.setStatuses(player.getCard(i), true);

							if (player.getCard(i).getRank() == Card::SIEBEN)
							{
								player.dealCard(i, card_stack);
								choose_wishcard = true;
							}
							else
							{
								player.dealCard(i, card_stack);
								logic.m_playersTurn = false;
								logic.m_enemysTurn = true;

								if (is_hosting)
									player.m_host.send_choice_information();
								else
									player.m_client.send_choice_information();
								
								if (player.getHandSize() == 0)
									return ReturnCodes::WON;

								continue;
							}

						}
						else
						{
							if (logic.m_playersTurn)
							{
								wrong_card_string = player.getCard(i).getCardName() + " doesn't fit " + card_stack.back().getCardName() + "!";
								wrong_card = true;
							}
							else // will never get here, so it's redundant, need to place it somewhere else.. 
							{
								wrong_card_string = "It is not your turn!";
								wrong_card = true;
							}
						}
					}
				}

				if (back_card.getGlobalBounds().contains(mouse_pos) && logic.m_playersTurn)
				{
					player.drawCard(deck.dealCard(player.getCoord(mouse_left_pressed), card_stack));
					logic.m_enemysTurn = true;
					logic.m_playersTurn = false;

					if (is_hosting)
						player.m_host.send_choice_information();
					else
						player.m_client.send_choice_information();

					continue;
				}
			}
			else
				player.set_moving_status(false);
		}
		
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP /////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (logic.m_enemysTurn)
		{
			for (int i{ 0 }; i < 1; ++i)
			{
				if (logic.enemySkips() && logic.m_enemysTurn)
				{
					logic.m_enemysTurn = false;
					logic.m_enemySkips = false;
					logic.m_playersTurn = true;

					std::cout << "The enemy skips a round.\n\n";
					continue;
				}

				if (!thread_has_been_enlisted)
				{
					// enlist thread
					thread_has_been_enlisted = true;
					thread_is_ready = false;
					std::cout << "enlisting thread..\n";

					std::thread get_enemys_move{ &OnlineEnemy::getNextMove, &enemy, &error_flag };
					get_enemys_move.detach();
				}
				if (thread_has_been_enlisted)
				{
					if (error_flag == sf::Socket::Status::Disconnected)
						return ReturnCodes::LOST_CONNECTION;

					else if (enemy.m_host->modify_buffer(false).is_valid || enemy.m_client->modify_buffer(false).is_valid)
					{
						if (is_hosting)
							enemys_move = &enemy.m_host->modify_buffer(false);
						else
							enemys_move = &enemy.m_client->modify_buffer(false);

						if (enemys_move->is_valid)
						{
							std::cout << "content: " << Card{ static_cast<Card::CardTyp>(enemys_move->card_typ), static_cast<Card::CardRank>(enemys_move->card_rank) } << std::endl;
							thread_is_ready = true;
						}
						else
							thread_is_ready = false;
					}
					else
					{
						thread_is_ready = false;
					}
				}

				if (thread_is_ready && logic.m_enemysTurn && enemys_move->is_valid)
				{
					// enemy draws a card
					if (enemys_move->uses_card)
					{
						// find card in his hand
						std::cout << "Parsing enemy move..\n";

						int index_of_enemy_card{ 0 };
						bool parsing_completed{ false };
						for (int i{ 0 }; i < enemy.getHandSize(); ++i)
						{
							if (enemys_move->card_typ == enemy.m_enemyHand[i].getTyp() &&
								enemys_move->card_rank == enemy.m_enemyHand[i].getRank())
							{
								std::cout << "Successfully parsed with index " << i << ".\n";
								for (int i{ 0 }; i < 20; ++i) std::cout << "-";
								std::cout << '\n';
								index_of_enemy_card = i;
								parsing_completed = true;

								// invalidate old packet
								enemys_move->is_valid = false;
							}
						}

						if (!parsing_completed)
						{
							std::cerr << "ERROR: Parsing has failed!\n";
							for (int i{ 0 }; i < 20; ++i) std::cout << "-";
							std::cout << '\n';

							assert(false && "Couldn't parse packet information correctly\n");
						}

						
						if (logic.m_enemyHasToDraw)
						{
							if (enemy.m_enemyHand[index_of_enemy_card].getRank() == Card::BUBE)
							{
								std::cout << "enemys seems to be having to draw\n";
								logic.m_enemysTurn = false;
								logic.m_playersTurn = true;
								logic.m_enemyHasToDraw = false;
							}

							else 
							{
								std::cout << "enemy draws: " << logic.m_amountOfCardsToDraw << " cards\n";
								for (int i{ 0 }; i < logic.m_amountOfCardsToDraw; ++i)
								{
									int amountOfCards{ enemy.getHandSize() };
									if (amountOfCards++ % 2 == 0)
										enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, card_stack));
									else
										enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, card_stack));

									enemy.m_xOffset += 50;
								}
								logic.m_amountOfCardsToDraw = 0;
								logic.m_enemysTurn = false;
								logic.m_playersTurn = true;
								logic.m_enemyHasToDraw = false;
								thread_has_been_enlisted = false;
								continue;
							}
						}
						if (logic.validateMove(enemy.m_enemyHand[index_of_enemy_card], card_stack.back(), false))
						{
							std::cout << "internally validated move\n";

							logic.m_startWunschKarteAktiv = false;
							logic.m_wunschkarteAktiv = false;

							std::cout << "setting statuses..\n";
							logic.setStatuses(enemy.m_enemyHand[index_of_enemy_card], false);

							if (enemy.m_enemyHand[index_of_enemy_card].getRank() == Card::SIEBEN)
							{
								logic.m_wunschkarte.setTyp(static_cast<Card::CardTyp>(enemys_move->wishcard_value));
								logic.m_wunschkarteAktiv = true;
							}

							enemy.dealCard(index_of_enemy_card);
							logic.m_enemysTurn = false;
							logic.m_playersTurn = true;

							if (enemy.getHandSize() == 0)
								return ReturnCodes::LOST;

							// allow to enlist new thread next iteration
							thread_has_been_enlisted = false;
							continue;
						}
						else
						{
							std::cout << enemy.m_enemyHand[index_of_enemy_card]
								<< "cant be used on " << card_stack.back() << '\n';

							std::cerr << "ERROR: logic::validateMove failed\n";

							assert(false && "INTERNAL VALIDATION FAILURE");
						}
					}
					else if (enemys_move->is_valid)
					{
						if (!enemys_move->uses_card)
						{

							std::cout << "enemys packet contains a draw\n";

							int amountOfCards{ enemy.getHandSize() };

							for (int i{ 0 }; i < enemys_move->amount_of_cards_drawn; ++i)
							{
								if (amountOfCards++ % 2 == 0)
									enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, card_stack));
								else
									enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, card_stack));
								enemy.m_xOffset += 50;
							}

							logic.m_enemyHasToDraw = false;
							logic.m_amountOfCardsToDraw = 0;

							logic.m_enemysTurn = false;
							logic.m_playersTurn = true;

							// allow to enlist new thread next iteration
							thread_has_been_enlisted = false;

							// invalidate old packet
							enemys_move->is_valid = false;

							continue;
						}
					}
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////DRAWING DRAWING DRAWING DRAWING DRAWING////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// draw table
		gameWindow.draw(playTable);

		// draw playerHand
		for (int i{ 0 }; i < player.getHandSize(); ++i)
		{
			sf::Vector2f position{ player.getCard(i).getGraphicalCard().getPosition() };
			gameWindow.draw(player.getCard(i).getGraphicalCard());
		}

		// draw enemyHand //
		enemy.m_xOffset = 0;
		for (int i{ 0 }; i < enemy.getHandSize(); ++i)
		{
			if (i % 2 == 0)
				enemy.m_enemyHand[i].getGraphicalCard().setPosition(sf::Vector2f((windowSettings::windowX / 3 + enemy.m_xOffset), 100));
			else
				enemy.m_enemyHand[i].getGraphicalCard().setPosition(sf::Vector2f((windowSettings::windowX / 3 + enemy.m_xOffset), 115));
			enemy.m_xOffset += 60;

			if (logic.viewEnemyHand())
				gameWindow.draw(enemy.m_enemyHand[i].getGraphicalCard());
			else
			{
				enemy.m_enemyHand[i].getGraphicalCard().setTexture(rueckseiten[0], true);
				gameWindow.draw(enemy.m_enemyHand[i].getGraphicalCard());
			}
		}

		// draw cardStack //
		card_stack.back().setPosition(windowSettings::windowX / 2 - 50, windowSettings::windowY / 2 - 50);
		gameWindow.draw(card_stack.back().getGraphicalCard());

		// draw deck //
		bool drawDeck{ true };
		switch (deck.m_deck.size())
		{
		case 0: drawDeck = false; break;
		case 1: back_card.setTexture(rueckseiten[0], true); break;
		case 2: back_card.setTexture(rueckseiten[1], true); break;
		case 3: back_card.setTexture(rueckseiten[2], true); break;
		default: back_card.setTexture(rueckseiten[3], true); break;
		}

		if (drawDeck)
			gameWindow.draw(back_card);

		// draw secondary //
		if (logic.wunschkarteAktiv())
		{
			gameWindow.draw(logic.getWunschkarteSprite());
		}

		if (choose_wishcard)
			for (unsigned int i{ 0 }; i < choose_wish_card_sprites.size(); ++i)
				gameWindow.draw(choose_wish_card_sprites[i].getGraphicalCard());

		if (wrong_card)
		{
			sf::Text wrongCardInfo{ wrong_card_string, my_font, 40u };
			wrongCardInfo.setPosition((windowSettings::windowX / 2) - (wrongCardInfo.getGlobalBounds().width / 2), windowSettings::windowY * 0.25);
			gameWindow.draw(wrongCardInfo);
		}

		if (logic.m_playerHasToDraw)
			gameWindow.draw(additional_info_text);

		// Only to test, will replace with If-else 
		if (logic.m_enemysTurn)
			turn_info.setString("Enemy's turn");
		else
			turn_info.setString("Your turn");
			
		gameWindow.draw(turn_info);

		// draw feed  //
		std::array<sf::Text, 5> killFeed;
		float xOffset{ 0 };
		for (unsigned int i{ 0 }; i < killFeed.size(); ++i)
		{
			killFeed[i] = sf::Text(logic.getFeedString(i), my_font, 20u);
			killFeed[i].setPosition(10, ((windowSettings::windowY * 0.13) - xOffset));
			xOffset += 25;
			gameWindow.draw(killFeed[i]);
		}

		// display //
		gameWindow.display();
	}

	// return exit if the gameWindow was closed
	return ReturnCodes::EXIT;
}
