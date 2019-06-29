#include "headers/TextureHandler.hpp"



// informations in the .h

void TextureHandler::init_font(sf::Font& init_this)
{
	init_this.loadFromFile("../resources/font/testFont.ttf");
}

void TextureHandler::init_backcard(std::array<sf::Texture, 4>& rueckseiten)
{
	rueckseiten[0].loadFromFile("../resources/images/rueckseite/einzel.jpg");
	rueckseiten[1].loadFromFile("../resources/images/rueckseite/zwei.png");
	rueckseiten[2].loadFromFile("../resources/images/rueckseite/drei.png");
	rueckseiten[3].loadFromFile("../resources/images/rueckseite/vier.png");
}

void TextureHandler::init_backcard_sprite(sf::Sprite& init_this)
{
	init_this.scale(0.4f, 0.4f);
	init_this.setOrigin(init_this.getGlobalBounds().width, init_this.getGlobalBounds().height);
	init_this.setPosition(1250.0f, 250.0f);
}

void TextureHandler::init_wish_card_sprites(std::array<Card, 4>& init_this)
{
	float yOffset{ 0 };

	for (unsigned int i{ 0 }; i < init_this.size(); ++i)
	{
		init_this[i].getGraphicalCard().setPosition(sf::Vector2f(150.0, 400.0 + yOffset));
		init_this[i].getGraphicalCard().setTexture(otherTextureArr[static_cast<myTextures::OtherTextures>(i)]);
		init_this[i].getGraphicalCard().setScale(1.0, 1.0);
		switch (i)
		{
		case 0: init_this[i].setTyp(Card::PIROS); break;
		case 1: init_this[i].setTyp(Card::TOECK); break;
		case 2: init_this[i].setTyp(Card::MOCK); break;
		case 3: init_this[i].setTyp(Card::ZOELD); break;
		}
		yOffset += 100;
	}
}
