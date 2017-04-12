/*
Load image and map as texture and sprite

**For now monster and player sprites' informations are saved here
But in future they should be seperated.

*/
#include "loadImage.h"
#include <SFML\Graphics.hpp>


loadImage::loadImage()
{

	zombieTexture = seperateImage(100, 0, 100, 200);
	charTexture = seperateImage(0, 0, 100, 200);
}

sf::Texture loadImage::seperateImage(int left, int top, int width, int height)
{
	sf::IntRect area;
	area = sf::IntRect(left, top, width, height);
	fullImage.loadFromFile("fullImage.jpg", area);
	return fullImage;
}

sf::Texture loadImage::getCharTexture()
{
	return charTexture;
}

sf::Sprite loadImage::getPlyrSprite()
{
	charSprite.setTexture(charTexture);
	charSprite.setScale(sf::Vector2f(0.1f, 0.075f));
	charSprite.setOrigin(charTexture.getSize().x / 2, charTexture.getSize().y / 2);

	return charSprite;
}

sf::Sprite loadImage::getZombieSprite(int i)
{
	switch (i)
	{
	case 1:
		zombieSprite.setTexture(zombieTexture);
		zombieSprite.setScale(sf::Vector2f(0.1f, 0.075f));
		zombieSprite.setOrigin(zombieTexture.getSize().x / 2, zombieTexture.getSize().y / 2);
		break;

	}
	return zombieSprite;
}