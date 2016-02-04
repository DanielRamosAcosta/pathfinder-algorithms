#pragma once

#include "map.hpp"
#include "common.hpp"
#include "point.hpp"

class maze_t{
private:
	map_t map_;
	unsigned seed_;
	bool have_seed_;
private:
	void carve_passages_from(point_t point);
	bool adjacent_ocupable_cell_exists(point_t point);
	bool reachable(point_t point);
	bool only_one_adyacent(point_t, dir_t direction);
	point_t random_ocupable_cell(point_t point);
	void clean(void);
public:
	maze_t(unsigned, unsigned);
	cell_t& at(unsigned, unsigned);
	cell_t& at(point_t);
	void generate(void);
	void generate(unsigned);
	unsigned x(void);
	unsigned y(void);

	friend std::ostream& operator<<(std::ostream &os, const maze_t &maze);
};