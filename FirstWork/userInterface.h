#pragma once


#include <SFML\Graphics.hpp>
class userInterface
{

public:
	userInterface();
	//void userInterface::setSprite(sf::Image c_Image);
	sf::Sprite getCharImage();
	sf::Texture getTexture();
	sf::Texture seperateImage(int left, int top, int width, int height);
private:
	sf::Texture c_Texture;
	sf::Sprite c_sprite;
};