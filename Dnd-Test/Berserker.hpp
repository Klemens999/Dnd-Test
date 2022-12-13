#pragma once
#include "Enemy.hpp"

class Berserker : public Enemy
{
public:
	Berserker(int x = 0, int y = 0) {
		speed = 2;
		ini = 3;
		hp = 30;
		dmg = 10;
		pos.x = x;
		pos.y = y;
		cRange = 1;
		sRange = 2;
		eclass = EClass::Berserker;
		sprite = "B";
	};
	~Berserker();
	std::pair<int, int> patrol() override;
	std::pair<int, int> takeAction() override;
	int getHp() override;
	void takeDmg(int attack) override;
	void attack(Entity& other) override;
	bool isEnemyInSight() override;
	void react(Enemy* e, std::vector<Enemy*> vec) override;
};

