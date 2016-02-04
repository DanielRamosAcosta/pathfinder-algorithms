#pragma once
#include <vector>
#include <iostream>

#include "common.hpp"

class map_t{
private:
	std::vector<std::vector<cell_t> > map_;
	cell_t default_;
public:
	map_t(unsigned, unsigned);
	map_t(unsigned, unsigned, cell_t);
	void resize(unsigned, unsigned);
	void clear(void);
	unsigned x(void) const;
	unsigned y(void) const;
	unsigned& at(unsigned x, unsigned y);
	unsigned at(unsigned x, unsigned y) const;
	std::ostream& print(std::ostream& os);
};