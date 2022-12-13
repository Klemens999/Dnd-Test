#pragma once
#include "Enemy.hpp"

class Dummy : public Enemy
{
public:
	Dummy(int h, int x, int y) {
		hp = h;
		pos.x = x;
		pos.y = y;
		sRange = 2;
	}
	std::pair<int, int> patrol() override;
	std::pair<int, int> takeAction() override;
	void move(int x, int y) override;
	void attack(Entity& other) override;
	bool isEnemyInSight() override;
	void react(Enemy* e, std::vector<Enemy*> vec) override;
};

