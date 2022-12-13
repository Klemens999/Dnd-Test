#include "pch.h"
#include "Goblin.hpp"

void Goblin::react(Enemy* e, std::vector<Enemy*> vec)
{
	if (checkForAllies()) {
		e->takeDmg(10);
	}
	else {
		pos.y += 1;
	}
}

bool Goblin::checkForAllies()
{
	for (auto entity : visableEntities) {
		auto enemy = dynamic_cast<Enemy*>(entity);
		if (enemy->getClass() == EClass::Goblin)
			return true;
	}
	return false;
}

std::pair<int, int> Goblin::patrol()
{
	std::pair<int,int> enemyNotPresent = std::make_pair(1, 1);
	if (!visableEntities.empty()) {
		state = State::Alert;
		return std::make_pair(0, 0);
	};
	return enemyNotPresent;
}

std::pair<int, int> Goblin::takeAction()
{
	std::pair<int, int> result{};
	switch (state) {
	case State::Idle:
		state = State::Patrol;
	case State::Patrol:
		result = patrol();
		break;
	case State::Alert:
		break;
	}
	std::cout << "Goblin " << id << std::endl;
	std::cout << "Iniciative: " << std::endl;
	std::cout << this->ini << std::endl;
	return result;
}

int Goblin::getHp()
{
	return hp;
}

void Goblin::takeDmg(int attack)
{
	hp -= attack;
	std::cout << __func__ << " Goblin: " << id << " has taken damage: " << attack << std::endl;
	if (hp <= 0) {
		isDead = true;
		std::cout << __func__ << " Goblin: " << id << " is dead." << std::endl;
	}
}

void Goblin::attack(Entity& other)
{
	if (isInCombatRange(other))
		other.takeDmg(dmg);
}

bool Goblin::isEnemyInSight()
{
	return !visableEntities.empty();
}
