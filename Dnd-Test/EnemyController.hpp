#pragma once
#include "Enemy.hpp"
#include "Berserker.hpp"
#include "Goblin.hpp"
#include <algorithm>

class EnemyController
{
	std::vector<Enemy*> enemies{};
	std::vector<Entity*> entities{};
public:
	EnemyController() {};
	void addEnemy(Enemy* e);
	void addEntity(Entity* e);
	void moveEnemy(Enemy* e, int offX, int offY);
	void checkVisibility(Enemy* e);
	void fight(Enemy* e, Enemy* e2);
	void nextTurn();
	void deleteEnemy(Enemy* e);
};


