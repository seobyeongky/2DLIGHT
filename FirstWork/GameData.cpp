#include "GameData.h"


int GameData::zombie_count;
GameData::GameData()
	:  _zombie(new zombie*[3]),
	_player (new Player*){}

//GameData::GameData(int i)
//	:_zombie(new zombie*[i]){}

void GameData::setIndex(int index) { zombie_index = index; }
void GameData::setZombie(zombie* zombie_ptr)
{ 
	*(_zombie + zombie_count) = zombie_ptr; 
	zombie_count++;
}

void GameData::setPlayer(Player* player_ptr) {*_player = player_ptr; }

zombie* GameData::getZombie(int index) { return *(_zombie + (index)); }
Player* GameData::getPlayer() { return *_player; }
int GameData::getIndex() { return zombie_index; }