#include "pch.h"
#include "Cell.hpp"
#include "Map.hpp"
#include "EnemyController.hpp"
#include "Barrel.hpp"
#include "Dummy.hpp"
#include <memory>


class EnemyControllerShould : public testing::Test{
public:
	std::shared_ptr<Enemy> gob = std::make_shared<Goblin>(0, 2);
	std::shared_ptr<Enemy> gob2 = std::make_shared<Goblin>(0, 5);
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>(0, 0);
	std::shared_ptr<Entity> barrel = std::make_shared<Barrel>(3, 2);
	std::shared_ptr<Enemy> dum = std::make_shared<Dummy>(20, 2, 0);
	EnemyController sut{};
	void SetUp() {
		sut.addEnemy(gob.get());
		sut.addEnemy(gob2.get());
		sut.addEnemy(ber.get());
		sut.addEnemy(dum.get());
		sut.addEntity(barrel.get());
	}
};

TEST_F(EnemyControllerShould, EnemyWithHighestIniciativeGoesFirst) {
	sut.deleteEnemy(dum.get());
	sut.moveEnemy(ber.get(), 0, 1);
	sut.nextTurn();
	sut.nextTurn();
	sut.nextTurn();
	sut.nextTurn();
	sut.nextTurn();
	sut.nextTurn();
	sut.nextTurn();
}

TEST_F(EnemyControllerShould, IfHpIs0EnemyDisappears) {
	sut.moveEnemy(ber.get(), 0, 1);
	sut.fight(ber.get(), gob.get());
	sut.moveEnemy(ber.get(), 0, 1);
	sut.fight(ber.get(), gob.get());
	sut.nextTurn();
	EXPECT_EQ(ber->getVisableEntities().size(), 1);
}

TEST_F(EnemyControllerShould, BerserkerAttacksNearDummyDuringHisTurn) {
	
	sut.moveEnemy(ber.get(), 1, 0);
	
	sut.nextTurn();
	sut.nextTurn();
	EXPECT_EQ(dum->getHp(), 10);
}
/*   //ma ID +2
TEST(IDTest, SecondEntityWillHaveIdEquals2) {
	std::shared_ptr<Enemy> gob = std::make_shared<Goblin>(0, 2);
	std::shared_ptr<Enemy> gob2 = std::make_shared<Goblin>(0, 5);
	EXPECT_EQ(gob->getId(), gob2->getId()+1);
}
*/
TEST_F(EnemyControllerShould, GoblinCannotMoveOnCellThatHasABarrel) {
	sut.moveEnemy(gob.get(), 3, 0);
	auto result = std::make_pair<int, int>(0, 2);
	EXPECT_EQ(gob->getPosition(), result);
}

TEST(GoblinTest, GoblinAttackOnlyWhenInGroup) {
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>(0,0);
	std::shared_ptr<Enemy> gob = std::make_shared<Goblin>(0,1);
	EnemyController sut{};
	sut.addEnemy(ber.get());
	sut.addEnemy(gob.get());
	auto result = std::make_pair<int, int>(0, 2);
	sut.fight(ber.get(),gob.get());

	EXPECT_EQ(gob->getPosition(), result);

	sut.moveEnemy(ber.get(), 0, 1);
	std::shared_ptr<Enemy> gob2 = std::make_shared<Goblin>(1, 1);
	sut.addEnemy(gob2.get());
	sut.fight(ber.get(), gob2.get());

	EXPECT_EQ(ber->getHp(), 20);
}

TEST(EnemyTest, EnemyCanReturnWhichEntitiesItCanSee) {
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>();
	std::shared_ptr<Enemy> ber2 = std::make_shared<Berserker>(0, 2);
	std::shared_ptr<Enemy> ber3 = std::make_shared<Berserker>(0, 3);
	EnemyController sut{};
	sut.addEnemy(ber.get());
	sut.addEnemy(ber2.get());
	sut.addEnemy(ber3.get());
	std::vector<Entity*> result{ber2.get()};
	
	EXPECT_EQ(ber->getVisableEntities(), result);
};

TEST(EnemyControllerTest, MultipleEnemiesCanSeeEachOtherWhileInRangeAndNotOtherwise) {
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>();
	std::shared_ptr<Enemy> ber2 = std::make_shared<Berserker>(0, 2);
	std::shared_ptr<Enemy> ber3 = std::make_shared<Berserker>(0, 3);
	EnemyController sut{};
	sut.addEnemy(ber.get());
	sut.addEnemy(ber2.get());
	sut.addEnemy(ber3.get());
	EXPECT_TRUE(ber->isInSight(ber2.get()) && ber2->isInSight(ber.get()) && ber2->isInSight(ber3.get()) && ber3->isInSight(ber2.get()));
	EXPECT_FALSE(ber->isInSight(ber3.get()) && ber3->isInSight(ber.get()));
}

TEST(EnemyControllerTest, OneEnemyCannotSeeAnyone) {
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>();
	EnemyController sut{};

	sut.addEnemy(ber.get());
	EXPECT_FALSE(ber->isEnemyInSight());
}

TEST(EnemyControllerTest, EnemiesCanSeeEachOther) {
	std::shared_ptr<Enemy> ber = std::make_shared<Berserker>();
	std::shared_ptr<Enemy> ber2 = std::make_shared<Berserker>(0,2);
	EnemyController sut{};
	sut.addEnemy(ber.get());
	sut.addEnemy(ber2.get());

	EXPECT_TRUE(ber->isEnemyInSight());
	EXPECT_TRUE(ber2->isEnemyInSight());
}

TEST(BerserkTest, BerserkCanPatrol) {
	std::unique_ptr<Enemy> ber = std::make_unique<Berserker>();
	EnemyController sut{};
	sut.addEnemy(ber.get());
	sut.nextTurn();
	EXPECT_NE(ber->getPosition(), std::make_pair(0, 0));
}

TEST(EntityTest, MovingEntitiesAfectTheirSight) {
	std::shared_ptr<Enemy> sut = std::make_shared<Berserker>();
	std::shared_ptr<Enemy> sut2 = std::make_shared<Berserker>();
	EnemyController sut3{};
	sut3.addEnemy(sut.get());
	sut3.addEnemy(sut2.get());
	sut3.moveEnemy(sut.get(), 2, 0);

	EXPECT_TRUE(sut->isEnemyInSight());

	sut3.moveEnemy(sut.get(), 2, 0);
	EXPECT_FALSE(sut->isEnemyInSight());
}

TEST(EntityTest, EntitiesFightWhenNextToEachOtherOnly) {
	std::unique_ptr<Enemy> sut = std::make_unique<Berserker>();
	std::unique_ptr<Enemy> sut2 = std::make_unique<Berserker>();
	sut->move(1, 0);
	sut->attack(*sut2);
	EXPECT_EQ(sut2->getHp(), 20);
	sut->move(1, 0);
	sut->attack(*sut2);
	EXPECT_NE(sut2->getHp(), 10);
}

TEST(EntityTest, EntityMoves) {
	std::unique_ptr<Enemy> sut = std::make_unique<Berserker>();
	std::pair<int, int> result = { 3,0 };
	sut->move(3, 0);
	EXPECT_EQ(result, sut->getPosition());
}

TEST(EntityTest, CreatedEntitySpawnsOn0x0) {
	std::unique_ptr<Enemy> sut = std::make_unique<Berserker>();
	std::pair<int, int> result = { 0,0 };
	EXPECT_EQ(result, sut->getPosition());
}