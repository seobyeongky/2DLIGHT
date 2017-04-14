#pragma once
#include <SFML\Graphics.hpp>

#include "zombie.h"
#include "Player.h"
#include "loadImage.h"
class GameData {
public:
	GameData();
	GameData(int i);
	void setPlayer(Player* player);
	void setZombie(zombie* zombie_ptr);
	void setIndex(int index);
	zombie* getZombie(int index);
	Player* getPlayer();
	int getIndex();
	

	static int zombie_count;

private:
	Player** _player;
	zombie** _zombie;
	loadImage load_Image;
	int zombie_index;
	sf::Sprite tmp_Sprite;
	sf::Texture tmp_Texture;
	
};