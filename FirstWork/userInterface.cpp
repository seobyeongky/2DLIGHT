/*
UI CPP
*/

#include "userInterface.h"

#include <SFML\Graphics.hpp>

userInterface::userInterface()
{

	c_Texture = seperateImage(100, 0, 100, 200);
}

sf::Texture userInterface::seperateImage(int left, int top, int width, int height)
{
	sf::IntRect area;
	sf::Texture tempImage;
	area = sf::IntRect(left, top, width, height);
	tempImage.loadFromFile("fullImage.jpg", area);
	return tempImage;
}

sf::Texture userInterface::getTexture()
{
	return c_Texture;
}
sf::Sprite userInterface::getCharImage()
{


	c_sprite.setTexture(c_Texture);
	c_sprite.setScale(sf::Vector2f(0.1f, 0.075f));
	c_sprite.setOrigin(c_Texture.getSize().x / 2, c_Texture.getSize().y / 2);

	return c_sprite;
}


