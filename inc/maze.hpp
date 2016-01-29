#pragma once

#include "map.hpp"
#include "common.hpp"
#include "point.hpp"

class maze_t{
private:
	map_t map_;
	unsigned seed_;
private:
	void carve_passages_from(unsigned, unsigned);
	void set_borders(void);
public:
	maze_t(unsigned, unsigned);
	cell_t& at(unsigned, unsigned);
	cell_t& at(point_t);
	void generate(void);
	void generate(unsigned);
	bool adjacent_ocupable_cell_exists(unsigned, unsigned);
	bool reachable(unsigned, unsigned);
	bool only_one_adyacent(unsigned, unsigned);
	void random_ocupable_cell(unsigned& x, unsigned& y);
	void clean(void);
	unsigned x(void);
	unsigned y(void);
	std::ostream& print(std::ostream& os);
};