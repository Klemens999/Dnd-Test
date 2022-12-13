#pragma once
#include "Entity.hpp"
#include <cmath>

enum class EClass {Berserker,Goblin};

class Enemy : public Entity
{
protected:
	int cRange{};
	int sRange{};
	enum class State { Idle, Patrol, Alert, Fight };
	State state = State::Idle;
	int dmg{};
	std::vector<Entity*> visableEntities{};
	EClass eclass{};
	int speed{};
public:
	int ini{};
	bool isDead = false;
	virtual ~Enemy() {};
	virtual std::pair<int, int> getPosition() const {
		return std::make_pair(pos.x, pos.y);
	};
	virtual void move(int x, int y)
	{
		pos.x += x;
		pos.y += y;
	};
	virtual void attack(Entity& other) = 0;
	virtual bool isEnemyInSight() = 0;
	virtual std::pair<int, int> patrol() = 0;
	virtual std::pair<int,int> takeAction() = 0;
	virtual void react(Enemy* e, std::vector<Enemy*> vec) = 0;
	virtual EClass getClass() const {
		return eclass;
	};
	virtual bool isInCombatRange(Entity& other)
	{
		auto opos = other.getPosition();
		return abs(opos.first - this->pos.x) <= cRange && abs(opos.second - this->pos.y) <= cRange;
	};

	virtual bool isInSight(Entity* other) const
	{
		auto opos = other->getPosition();
		return abs(opos.first - this->pos.x) <= sRange && abs(opos.second - this->pos.y) <= sRange;
	};

	virtual std::vector<Entity*>getVisableEntities() const{
		return visableEntities;
	};

	virtual void checkVisableEntities(Entity* other)
	{
		if (isInSight(other)) {
			auto it = std::find(visableEntities.begin(), visableEntities.end(), other);
			if (it == visableEntities.end() && other != this) {
				visableEntities.emplace_back(other);
			}
		}
		else {
			auto it = std::remove(visableEntities.begin(), visableEntities.end(), other);
			if (it != visableEntities.end()) {
				visableEntities.erase(it);
			}
		}
	}
	virtual void eraseDeceasedEnemies(int id) {
		auto it = std::remove_if(visableEntities.begin(), visableEntities.end(),
			[id](auto entity) {return entity->getId() == id; });
		if (it != visableEntities.end()) {
			visableEntities.erase(it);
		}
	}
	virtual void takeDmg(int attack) {
		hp -= attack;
	}
	virtual Enemy* findNearestEnemy() {
		float closestDistance{};
		Enemy* closestEnemy = nullptr;
		for (auto& enemy : visableEntities) {
			auto opos = enemy->getPosition();
			auto c = hypot((0.f+ opos.first - this->pos.x), (0.f + opos.second - this->pos.y));
			if (closestDistance == 0 || c < closestDistance) {
				closestDistance = c;
				closestEnemy = dynamic_cast<Enemy*>(enemy);
			}
		}
		return closestEnemy;
	};
	virtual std::pair<int,int> chase(Enemy* chased) {
		//this ma x 1 y 2, opos ma x 3, y 1 -> nasza docelowa pozycja to 2,2 || 2,1
		int x{};
		int y{};
		std::pair<int, int> result{};
		auto opos = chased->getPosition();
		if (opos.first != this->getPosition().first) {
			x = abs(opos.first - this->getPosition().first);
			result.first = x<speed ? x - 1 : speed;
		}
		if (opos.second != this->getPosition().second) {
			y = abs(opos.second - this->getPosition().second);
			result.second = y < speed ? y - 1: speed;
		}
		return result;
	}
};

