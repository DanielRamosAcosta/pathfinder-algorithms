#pragma once
#include <vector>
#include <iostream>

#include "common.hpp"

class map_t{
private:
	std::vector<std::vector<tile_t>> map_;
	tile_t default_;
public:
	map_t(unsigned, unsigned);
	map_t(unsigned, unsigned, tile_t);
	void resize(unsigned, unsigned);
	void clear(void);
	unsigned x(void) const;
	unsigned y(void) const;
	tile_t& at(unsigned, unsigned);
	tile_t at(unsigned, unsigned) const;
	
	friend std::ostream& operator<<(std::ostream&, const map_t&);
};