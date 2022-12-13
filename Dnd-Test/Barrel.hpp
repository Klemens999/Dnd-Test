#pragma once
#include "Entity.hpp"

class Barrel :
    public Entity
{
public:
	Barrel(int x = 0, int y = 0) {
		hp = 10;
		pos.x = x;
		pos.y = y;
	};
	void move(int x, int y) override;
	int getHp() override;
	void takeDmg(int attack) override;
	std::pair<int, int> getPosition() const override;
};

