/*
loadImage.h
*/
#pragma once
#include <SFML/Graphics.hpp>

class loadImage {

public:
	loadImage();
	sf::Texture seperateImage(int left, int top, int width, int height);
	sf::Texture getCharTexture();
	sf::Texture getZombieTexture();
	sf::Sprite getPlyrSprite();
	sf::Sprite getZombieSprite(int i);

private:
	sf::Sprite charSprite;
	sf::Sprite zombieSprite;


	sf::Texture fullImage;
	sf::Texture zombieTexture;
	sf::Texture charTexture;
};