#include "pch.h"
#include "Barrel.hpp"


void Barrel::move(int x, int y)
{
	pos.x += x;
	pos.y += y;
}

int Barrel::getHp()
{
	return hp;
}

void Barrel::takeDmg(int attack)
{
	hp -= attack;
}

std::pair<int, int> Barrel::getPosition() const
{
	return std::make_pair(pos.x, pos.y);
}
