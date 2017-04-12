#include "GameData.h"

GameData::GameData()
	: zombie_count(0), _zombie(new zombie*[3]){}

//GameData::GameData(int i)
//	:_zombie(new zombie*[i]){}

//sf::Texture GameData::getTexture() { return tmp_Texture; }
//sf::Sprite GameData::getSprite(int sprite_num)
//{
//	switch (sprite_num)
//	{
//	case 1:
//		tmp_Sprite = load_Image.getPlyrSprite();
//		break;
//	case 2:
//		tmp_Sprite = load_Image.getZombieSprite(sprite_num-1);
//		break;
//	}
//	return tmp_Sprite;
//}
void GameData::setIndex(int index) { zombie_index = index; }
void GameData::setZombie(zombie* zombie_ptr)
{ 
	*(_zombie + zombie_count) = zombie_ptr; 
	zombie_count++;
}

void GameData::setPlayer(Player player) { _player = player; }

zombie* GameData::getZombie(int index) { return *(_zombie + (index)); }
Player GameData::getPlayer() { return _player; }
int GameData::getIndex() { return zombie_index; }