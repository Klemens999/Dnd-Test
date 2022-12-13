#pragma once
namespace {
	static int nextId = 0;
}

class Entity
{
protected:
	struct Position {
		int x{};
		int y{};
	};
	int hp{};
	Position pos{};
	const int id;
public:
	std::string sprite{};
	Entity() : id(++nextId) {};
	virtual ~Entity() {
		--nextId;
	};
	virtual void move(int x, int y) = 0;
	virtual int getHp() {
		return hp;
	};
	virtual void takeDmg(int attack) = 0;
	virtual std::pair<int, int> getPosition() const = 0;
	virtual int getId() {
		return id;
	}
};