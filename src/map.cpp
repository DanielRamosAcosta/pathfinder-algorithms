#include "map.hpp"

map_t::map_t(unsigned altura, unsigned anchura):
default_(0)
{
	resize(anchura, altura);
}

map_t::map_t(unsigned altura, unsigned anchura, cell_t val):
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

unsigned& map_t::at(unsigned x, unsigned y)
{
	return map_[x][y];
}

unsigned map_t::at(unsigned x, unsigned y) const
{
	return map_[x][y];
}

std::ostream& map_t::print(std::ostream& os)
{
	for(unsigned i = 0; i < y(); i++){
		for(unsigned j = 0; j < x(); j++){
			os << map_[j][i] << " ";
		}
		os << "\n";
	}
	return os;
}