#pragma once
#include <SFML\Graphics.hpp>

#include "zombie.h"
#include "Player.h"
#include "loadImage.h"
class GameData {
public:
	GameData();
	//GameData(int i);
	/*sf::Texture getTexture();
	sf::Sprite getSprite(int sprite_num);*/
	void setPlayer(Player player);
	void setZombie(zombie* zombie_ptr);
	void setIndex(int index);
	zombie* getZombie(int index);
	Player getPlayer();
	int getIndex();
	

	int zombie_count = 0;

private:
	Player _player;
	zombie** _zombie;
	loadImage load_Image;
	int zombie_index;
	sf::Sprite tmp_Sprite;
	sf::Texture tmp_Texture;
	
};