
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Card.hpp"
#include "Deck.hpp"
#include <array>
#include "textureArray.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "Logic.hpp"
#include "TextureHandler.hpp"
#include "ReturnCodes.hpp"


int singleplayer(sf::RenderWindow &gameWindow, Logic &logic, const sf::Texture &playTableTexture)
{
	sf::RectangleShape playTable(sf::Vector2f(windowSettings::windowX, windowSettings::windowY));
	playTable.setTexture(&playTableTexture);

	std::array<sf::Texture, 4> rueckseiten;
	TextureHandler::init_backcard(rueckseiten);
	
	sf::Sprite backCard;
	backCard.scale(0.4f, 0.4f);
	backCard.setOrigin(backCard.getGlobalBounds().width, backCard.getGlobalBounds().height);
	backCard.setPosition(1250.0f, 250.0f);

	Deck deck;
	Player player(&logic);
	Enemy enemy(&logic);

	std::string additionalInfo{ "" };
	sf::Font myFont;
	myFont.loadFromFile("../resources/font/testFont.ttf");

	sf::Text turn_info{ "Your turnX", myFont, 25 };
	turn_info.setPosition(windowSettings::windowX / 20 * 1 - turn_info.getGlobalBounds().width / 2,
		windowSettings::windowY / 10 * 3);

	sf::Clock myClock;
	sf::Clock frameTime;
	sf::Time checkTime;

	std::array<Card, 4> chooseWunschKarteSprite;
	float yOffset{ 0 };

	logic.resetFeed();
	logic.resetStatuses();

	for (unsigned int i{ 0 }; i < chooseWunschKarteSprite.size(); ++i)
	{
		chooseWunschKarteSprite[i].getGraphicalCard().setPosition(sf::Vector2f(150.0, 400.0 + yOffset));
		chooseWunschKarteSprite[i].getGraphicalCard().setTexture(otherTextureArr[static_cast<myTextures::OtherTextures>(i)]);
		chooseWunschKarteSprite[i].getGraphicalCard().setScale(1.0, 1.0);
		switch (i)
		{
		case 0: chooseWunschKarteSprite[i].setTyp(Card::PIROS); break;
		case 1: chooseWunschKarteSprite[i].setTyp(Card::TOECK); break;
		case 2: chooseWunschKarteSprite[i].setTyp(Card::MOCK); break;
		case 3: chooseWunschKarteSprite[i].setTyp(Card::ZOELD); break;
		}
		yOffset += 100;
	}
	bool chooseWunschkarte{ false };
	
	std::vector<Card> cardStack;
	cardStack.push_back(deck.dealCard());

	switch (cardStack.back().getRank())
	{
	case Card::SIEBEN: logic.m_startWunschKarteAktiv = true; break;
	case Card::ASS: logic.m_playerSkips = true; break;
	case Card::BUBE: logic.m_playerHasToDraw = true; logic.m_amountOfCardsToDraw += 2; break;
	}

	bool mouseLeftPressed{ false };
	bool mouseLeftReleased{ false };

	for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i) // init playerHand
	{
		player.drawCard(deck.dealCard(sf::Vector2f{ (windowSettings::windowX / (logic.m_sizeOfStartHand - 2)) + player.m_xOffset, windowSettings::windowY * 0.8f }, cardStack));
		player.m_xOffset += 100;
	}
	for (int i{ 0 }; i < logic.m_sizeOfStartHand; ++i) // init enemyHand
	{
		if (i % 2 == 0)
			enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, cardStack));
		else
			enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, cardStack));

		enemy.m_xOffset += 50;
	}

	std::cout << "Startkarte " << cardStack.back() << "\n";
	
	while (gameWindow.isOpen())
	{
		sf::Event evnt;
		sf::Vector2f cardStackPos{ cardStack.back().getGraphicalCard().getPosition() };
		sf::Vector2f mousePos{ sf::Mouse::getPosition(gameWindow) };
		bool wrongCard{ false };
		std::string wrongCardString{ "" };

		while (gameWindow.pollEvent(evnt))
		{
			if (evnt.type == sf::Event::Closed)
			{
				gameWindow.close();
			}

			if (evnt.type == sf::Event::MouseButtonPressed)
			{
				if (evnt.mouseButton.button == sf::Mouse::Left)
				{
					mouseLeftPressed = true;
					mouseLeftReleased = false;
					//std::cout << "MOUSEBUTTON PRESSED\n";
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


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //// PLAYER LOOP //////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i{ 0 }; i < 1; ++i) // player loop
		{
			/*if (!logic.m_playersTurn)
				continue;*/
			if (logic.playerSkips())
			{
				logic.m_playersTurn = false;
				logic.m_playerSkips = false;
				std::cout << "Du musst eine Runde aussetzen.\n";
				logic.m_enemysTurn = true;
				myClock.restart();

				continue;
			}

			if (logic.m_playerHasToDraw)
			{
				additionalInfo = "Du musst " + std::to_string(logic.m_amountOfCardsToDraw) + " Karten ziehen!";
				bool hasDrawCards{ false };
				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (player.getCard(i).getRank() == Card::BUBE)
					{
						hasDrawCards = true;
						break;
					}
				}

				if (hasDrawCards)
				{
					if (backCard.getGlobalBounds().contains(mousePos) && mouseLeftPressed && !mouseLeftReleased)
					{
						for (int i{ 0 }; i < logic.m_amountOfCardsToDraw; ++i)
							player.drawCard(deck.dealCard(player.getCoord(mouseLeftPressed), cardStack));

						logic.m_playerHasToDraw = false;
						logic.m_amountOfCardsToDraw = 0;
						logic.m_enemysTurn = true;
						logic.m_playersTurn = false;
						continue;
					}
				}

				else
				{
					for (int i{ 0 }; i < logic.m_amountOfCardsToDraw; ++i)
						player.drawCard(deck.dealCard(player.getCoord(mouseLeftPressed), cardStack));

					logic.m_playerHasToDraw = false;
					logic.m_amountOfCardsToDraw = 0;
					logic.m_enemysTurn = true;
					logic.m_playersTurn = false;
					continue;
				}
			}

			if (mouseLeftPressed && !mouseLeftReleased)
			{
				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (player.getCard(i).m_graphicalCard.getGlobalBounds().contains(sf::Vector2f(mousePos)))
					{
						player.move_card(mousePos, i);
						break;
					}
				}

				if (chooseWunschkarte)
				{
					for (unsigned int i{ 0 }; i < chooseWunschKarteSprite.size(); ++i)
					{
						if (chooseWunschKarteSprite[i].getGraphicalCard().getGlobalBounds().contains(mousePos))
						{
							logic.m_wunschkarte.setTyp(chooseWunschKarteSprite[i].getTyp());
							logic.m_wunschkarteAktiv = true;
							logic.m_enemysTurn = true;
							chooseWunschkarte = false;
							std::cout << "Du willst " << logic.m_wunschkarte.getTyp() << ".\n";
						}
					}
				}
				for (int i{ 0 }; i < player.getHandSize(); ++i)
				{
					if (cardStack.back().getGraphicalCard().getGlobalBounds().contains(player.getCard(i).getGraphicalCard().getPosition())
						&& logic.m_playersTurn)
					{
						if (logic.validateMove(player.getCard(i), cardStack.back(), true, logic.m_playerHasToDraw))
						{
							chooseWunschkarte = false;
							logic.m_startWunschKarteAktiv = false;
							logic.m_wunschkarteAktiv = false;
							logic.setStatuses(player.getCard(i), true);
							if (player.getCard(i).getRank() == Card::SIEBEN)
							{
								player.dealCard(i, cardStack);
								chooseWunschkarte = true;
								logic.m_playersTurn = false;
								logic.m_enemysTurn = false;
							}
							else
							{
								player.dealCard(i, cardStack);
								logic.m_playersTurn = false;
								logic.m_enemysTurn = true;
							}
							if (player.getHandSize() == 0)
								return ReturnCodes::WON;
						}
						else
						{
							if (logic.m_playersTurn)
							{
								wrongCardString = player.getCard(i).getCardName() + " passt nicht auf " + cardStack.back().getCardName() + "!";
								wrongCard = true;
							}
							else
							{
								wrongCardString = "Du bist nicht an der Reihe!";
								wrongCard = true;
							}
						}
					}
				}

				if (backCard.getGlobalBounds().contains(sf::Vector2f(mousePos)) && logic.m_playersTurn)
				{
					player.drawCard(deck.dealCard(player.getCoord(mouseLeftPressed), cardStack));
					logic.m_enemysTurn = true;
					logic.m_playersTurn = false;
					continue;
				}
			}
			else
				player.set_moving_status(false);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP //// ENEMY LOOP /////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool drawCard{ false };
		if (!logic.m_enemysTurn)
			myClock.restart();
		else
			checkTime = myClock.getElapsedTime();

		if (logic.m_enemysTurn
			// Simulate delay when the CPU mustn't skip
			&& (logic.m_enemySkips) ? true : checkTime.asMilliseconds() >= Deck::getRandomNumber(500, 1000))
		{
			checkTime = sf::Time{sf::Time::Zero};

			bool hasDrawCards{ false };
			logic.m_enemysTurn = false;
			for (int i{ 0 }; i < 1; ++i)
			{
				if (logic.enemySkips())
				{
					logic.m_enemysTurn = false;
					logic.m_enemySkips = false;
					logic.m_playersTurn = true;
					std::cout << "Der Gegner sitzt eine Runde aus.\n\n";
					continue;
				}

				if (logic.m_enemyHasToDraw)
				{
					for (int i{ 0 }; i < enemy.getHandSize(); ++i)
					{
						if (enemy.getCard(i).getRank() == Card::BUBE)
						{
							logic.setStatuses(enemy.getCard(i), false);
							enemy.dealCard(i, cardStack);
							hasDrawCards = true;
							logic.m_enemysTurn = false;
							logic.m_playersTurn = true;

							if (enemy.getHandSize() == 0)
								return ReturnCodes::LOST;

							break;
						}
					}
					if (hasDrawCards)
						continue;

					for (int i{ 0 }; i < logic.m_amountOfCardsToDraw; ++i)
					{
						int amountOfCards{ enemy.getHandSize() };
						if (amountOfCards++ % 2 == 0)
							enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, cardStack));
						else
							enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, cardStack));
						enemy.m_xOffset += 50;
					}
					logic.m_amountOfCardsToDraw = 0;
					logic.m_enemysTurn = false;
					logic.m_playersTurn = true;
					logic.m_enemyHasToDraw = false;
					continue;
				}

				enemy.determineBestCard(cardStack.back(), player.getHandSize(), logic.wunschkarteAktiv(), logic.getWunschkarte());

				for (int i{ 0 }; i < enemy.getHandSize(); ++i)
				{
					if (logic.validateMove(enemy.getCard(i), cardStack.back(), false))
					{
						logic.m_startWunschKarteAktiv = false;
						logic.m_wunschkarteAktiv = false;
						logic.setStatuses(enemy.getCard(i), false);
						if (enemy.getCard(i).getRank() == Card::SIEBEN)
						{
							enemy.determineBesteWunschKarte(enemy.getCard(i), logic.m_wunschkarte);
							logic.m_wunschkarteAktiv = true;
						}
						enemy.dealCard(i, cardStack);
						logic.m_enemysTurn = false;
						logic.m_playersTurn = true;
						if (enemy.getHandSize() == 0)
							return ReturnCodes::LOST;

						drawCard = false;
						break;
					}
					else
						drawCard = true;
				}

				if (drawCard)
				{
					int amountOfCards{ enemy.getHandSize() };
					if (amountOfCards++ % 2 == 0)
						enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 100 }, cardStack));
					else
						enemy.drawCard(deck.dealCard(sf::Vector2f{ windowSettings::windowX / 3 + enemy.m_xOffset, 125 }, cardStack));
					enemy.m_xOffset += 50;

					logic.m_enemysTurn = false;
					logic.m_playersTurn = true;
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////// DRAW // DRAW // DRAW ////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
	

		// draw table //
		gameWindow.draw(playTable);

		// draw playerHand //
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
				enemy.getCard(i).getGraphicalCard().setPosition(sf::Vector2f((windowSettings::windowX / 3 + enemy.m_xOffset), 100));
			else
				enemy.getCard(i).getGraphicalCard().setPosition(sf::Vector2f((windowSettings::windowX / 3 + enemy.m_xOffset), 115));
			enemy.m_xOffset += 60;

			if (logic.viewEnemyHand())
				gameWindow.draw(enemy.getCard(i).getGraphicalCard());
			else
			{
				enemy.getCard(i).getGraphicalCard().setTexture(rueckseiten[0], true);
				gameWindow.draw(enemy.getCard(i).getGraphicalCard());
			}
		}

		// draw cardStack //
		cardStack.back().setPosition(windowSettings::windowX / 2 - 50, windowSettings::windowY / 2 - 50);
		gameWindow.draw(cardStack.back().getGraphicalCard());

		// draw deck //
		bool drawDeck{ true };
		switch (deck.m_deck.size())
		{
		case 0: drawDeck = false; break;
		case 1: backCard.setTexture(rueckseiten[0], true); break;
		case 2: backCard.setTexture(rueckseiten[1], true); break;
		case 3: backCard.setTexture(rueckseiten[2], true); break;
		default: backCard.setTexture(rueckseiten[3], true); break;
		}

		if (drawDeck)
			gameWindow.draw(backCard);

		// draw secondary //
		if (logic.wunschkarteAktiv())
		{
			gameWindow.draw(logic.getWunschkarteSprite());
		}

		if (chooseWunschkarte)
			for (unsigned int i{ 0 }; i < chooseWunschKarteSprite.size(); ++i)
				gameWindow.draw(chooseWunschKarteSprite[i].getGraphicalCard());

		if (logic.m_playerHasToDraw)
		{
			sf::Text drawText{ additionalInfo, myFont, 40u };
			drawText.setFillColor(sf::Color::White);
			drawText.setPosition((windowSettings::windowX / 2) - (drawText.getGlobalBounds().width / 2), windowSettings::windowY * 0.25);
			gameWindow.draw(drawText);
		}

		if (logic.m_enemysTurn)
			turn_info.setString("Enemy's turn");

		if (logic.m_playersTurn)
			turn_info.setString("Your turn");

		gameWindow.draw(turn_info);

		if (wrongCard)
		{
			sf::Text wrongCardInfo{ wrongCardString, myFont, 40u };
			wrongCardInfo.setPosition((windowSettings::windowX / 2) - (wrongCardInfo.getGlobalBounds().width / 2), windowSettings::windowY * 0.25);
			gameWindow.draw(wrongCardInfo);
		}

		// draw feed  //
		

		std::array<sf::Text, 5> killFeed;
		float xOffset{ 0 };
		for (unsigned int i{ 0 }; i < killFeed.size(); ++i)
		{
			killFeed[i] = sf::Text(logic.getFeedString(i), myFont, 20u);
			killFeed[i].setPosition(10, ((windowSettings::windowY * 0.13) - xOffset));
			xOffset += 25;
			gameWindow.draw(killFeed[i]);
		}

		// display //
		gameWindow.display();
	}

	// Return -1 if the gamewindow closes
	return ReturnCodes::EARLY_EXIT;
}