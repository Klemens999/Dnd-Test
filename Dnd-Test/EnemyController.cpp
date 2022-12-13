#include "pch.h"
#include "EnemyController.hpp"

struct biggerIniciative
{
	inline bool operator() (const Enemy* struct1, const Enemy* struct2)
	{
		return (struct1->ini > struct2->ini);
	}
};

void EnemyController::addEnemy(Enemy* e)
{
	enemies.emplace_back(std::move(e));
	checkVisibility(e);
}

void EnemyController::addEntity(Entity* e)
{
	entities.emplace_back(std::move(e));
}

void EnemyController::moveEnemy(Enemy* e, int offX, int offY)
{
	auto pos = e->getPosition();
	for (auto entity : entities) {
		if (entity->getPosition() == std::make_pair(pos.first + offX, pos.second + offY)) {
			std::cout << __func__ << " Id: " << e->getId() << " couldnt move on this position." << std::endl;
			return;
		}
	}
	for (auto enemy : enemies) {
		if (enemy->getPosition() == std::make_pair(pos.first + offX, pos.second + offY)) {
			std::cout << __func__ << " Id: " << e->getId() << " couldnt move on this position." << std::endl;
			return;
		}
	}
	e->move(offX, offY);
	std::cout<< __func__ << " Id: " << e->getId() << " moves X: " << offX << " and moves Y: " << offY << std::endl;
	std::cout << "Its current position X: "<< e->getPosition().first <<" Y: " <<e->getPosition().second <<std::endl;
	checkVisibility(e);
}

void EnemyController::checkVisibility(Enemy* e) {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies.at(i)->checkVisableEntities(e);
		e->checkVisableEntities(enemies.at(i));
	}
}
void EnemyController::fight(Enemy* e, Enemy* e2)
{
	e->attack(*e2);
	e2->react(e,enemies);
}
void EnemyController::nextTurn()
{
	for (auto enemy : enemies) {
		checkVisibility(enemy);
	}
	
	for (size_t enemy = 0; enemy < enemies.size(); enemy++) {
		std::sort(enemies.begin(), enemies.end(), biggerIniciative());
		auto moveOffset = enemies[enemy]->takeAction();
		if (moveOffset.first != 0 || moveOffset.second != 0) {
			moveEnemy(enemies[enemy], moveOffset.first, moveOffset.second);
			
		}
		std::cout <<__func__<<" Handling: " << enemies[enemy]->getId() << " " << std::endl;
	}
	for (auto enemy : enemies) {
		if (enemy->isDead) {
			int deadId = enemy->getId();
			for (auto enemyCheck : enemies) {
				if (enemyCheck->getId() == enemy->getId()) continue;
				enemyCheck->eraseDeceasedEnemies(enemy->getId());
			}
			enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
		}
	}
}

void EnemyController::deleteEnemy(Enemy* e)
{
	enemies.erase(std::remove(enemies.begin(), enemies.end(), e), enemies.end());
}
	