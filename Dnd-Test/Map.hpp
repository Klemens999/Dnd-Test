#pragma once
#include "Cell.hpp"
#include <iostream>

class Map
{
	std::vector<Cell> map{};
	size_t width{};
	size_t height{};
public:
	Map(size_t x, size_t y) : width(x), height(y) {
		map.resize(x*y);
	};
};

