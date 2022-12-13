#include "pch.h"
#include "Berserker.hpp"

Berserker::~Berserker() {};

std::pair<int,int> Berserker::patrol()
{
	if (!visableEntities.empty()) {
		state = State::Alert;
		return std::make_pair(0,0);
	};
	// ruch w randomowym kierunku
	return std::make_pair(1,1);
}

std::pair<int, int> Berserker::takeAction()
{
	std::pair<int, int> result{};
	switch (state) {
	case State::Idle:
		state = State::Patrol;

	case State::Patrol:
		result = patrol();
		break;

	case State::Alert:
		for (auto enemy : visableEntities) {
			if (isInCombatRange(*enemy)) {
				state = State::Fight;
				std::cout <<__func__<< " Berserker entering fight state" << std::endl;
			}
			else {
				result = chase(findNearestEnemy());
				std::cout << __func__ << " Berserker chasing" << std::endl;
				break;
			}
		}

	case State::Fight:
		if (visableEntities.empty()) {
			state = State::Idle;
			std::cout << __func__ << " Berserker entering idle state" << std::endl;
			break;
		}
		//closestEnemy = dynamic_cast<Enemy*>(enemy);
		if (std::any_of(visableEntities.begin(), visableEntities.end(), [this](auto enemy) { 
			if (!dynamic_cast<Enemy*>(enemy)) return false;
			return isInCombatRange(*enemy); })) {
			for (auto enemy : visableEntities) {
				if (isInCombatRange(*enemy)) {
					attack(*enemy);
				}
			}
		}
		else {
			state = State::Alert;
			std::cout << __func__ << " Berserker entering alert state" << std::endl;
		}
	}
	std::cout << "Berserker " << id << std::endl;
	std::cout << "Iniciative: " << std::endl;
	std::cout << this->ini << std::endl;
	return result;
}



int Berserker::getHp()
{
	return hp;
}

void Berserker::takeDmg(int attack)
{
	hp -= attack;
	std::cout << __func__ << " Berserker: " << id << " has taken damage: " << attack << std::endl;
	if (hp <= 0) {
			isDead = true;
			std::cout << __func__ << " Berserker: " << id << " is dead." << std::endl;
	}
	
}

void Berserker::attack(Entity& other)
{
	if (isInCombatRange(other))
		other.takeDmg(dmg);
}

bool Berserker::isEnemyInSight()
{
	return !visableEntities.empty();
}

void Berserker::react(Enemy* e, std::vector<Enemy*>)
{
	state = State::Fight;
}


