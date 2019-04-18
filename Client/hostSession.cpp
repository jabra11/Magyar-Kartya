#include <array>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Logic.h"
#include "OnlinePlayer.h"
#include "OnlineEnemy.h"
#include "TextureHandler.h"
#include "Card.h"

int hostSession(sf::RenderWindow& gameWindow, Logic& logic, const sf::RectangleShape& playTable, OnlinePlayer& player)
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

	auto additional_info = std::string{ "" };

	Deck deck;
	auto card_stack = std::vector<Card>{};
	
	constexpr int port{ 55000 };
	OnlineEnemy enemy{ &logic, &deck, &card_stack, port, false };


	logic.resetFeed();
	logic.resetStatuses();

	player.m_host.send_deck_information(deck);



	// preliminary return statement
	return 0;
	///////////////////////////////
}