#include "pch.h"
#include "Dummy.hpp"

std::pair<int, int> Dummy::patrol()
{
    return std::make_pair<int, int>(0,0);
}

std::pair<int, int> Dummy::takeAction()
{
    return std::make_pair<int, int>(0,0);
}

void Dummy::move(int x, int y)
{
    return;
}

void Dummy::attack(Entity& other)
{
}

bool Dummy::isEnemyInSight()
{
    return false;
}

void Dummy::react(Enemy* e, std::vector<Enemy*> vec)
{

}

