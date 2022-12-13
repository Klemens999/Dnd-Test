#pragma once
#include "Enemy.hpp"

class Goblin : public Enemy
{
public:
	Goblin(int x = 0, int y = 0) {
		speed = 1;
		ini = 2;
		hp = 20;
		dmg = 10;
		pos.x = x;
		pos.y = y;
		cRange = 1;
		sRange = 2;
		eclass = EClass::Goblin;
		sprite = "G";
	};
	void react(Enemy* e, std::vector<Enemy*> vec) override;
	int getHp() override;
	void takeDmg(int attack) override;
	void attack(Entity& other)override;
	bool isEnemyInSight() override;
	std::pair<int, int> patrol() override;
	std::pair<int, int> takeAction() override;
	bool checkForAllies();
};

