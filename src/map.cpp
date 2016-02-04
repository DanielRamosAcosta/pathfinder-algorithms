#include "map.hpp"

map_t::map_t(unsigned altura, unsigned anchura):
default_(tile_t::empty)
{
	resize(anchura, altura);
}

map_t::map_t(unsigned altura, unsigned anchura, tile_t val):
default_(val)
{
	resize(anchura, altura);
}

void map_t::resize(unsigned x, unsigned y)
{
	map_.resize(x);
	for(auto &i : map_)
		i.resize(y, default_);
}

void map_t::clear(void)
{
	for(auto &i : map_)
		for(auto &j : i)
			j = default_;
}

unsigned map_t::x(void) const
{
	return map_.size();
}

unsigned map_t::y(void) const
{
	if(x() == 0)
		return 0;
	else
		return map_[0].size();
}

tile_t& map_t::at(unsigned x, unsigned y)
{
	return map_[x][y];
}

tile_t map_t::at(unsigned x, unsigned y) const
{
	return map_[x][y];
}

std::ostream& operator<<(std::ostream& os, const map_t& map)
{
	for(unsigned i = 0; i < map.y(); i++){
		for(unsigned j = 0; j < map.x(); j++){
			os << map.map_[j][i] << " ";
		}
		os << "\n";
	}
	return os;
}