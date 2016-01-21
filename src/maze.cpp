#include "maze.hpp"

maze_t::maze_t(unsigned x, unsigned y):
map_(x, y, tile::obstacle),
seed_(0)
{}

cell_t& maze_t::at(unsigned x, unsigned y)
{
	return map_.at(x, y);
}

void maze_t::generate(void)
{
	map_.clear();
	carve_passages_from(1, 1);
	clean();
}

void maze_t::generate(unsigned seed)
{
	seed_ = seed;
	std::srand(seed_);
	generate();
	seed_ = 0;
}

void maze_t::carve_passages_from(unsigned x, unsigned y)
{
	map_.at(x, y) = tile::empty;
	unsigned nx, ny;
	while(adjacent_ocupable_cell_exists(x, y)){
		nx = x;
		ny = y;
		random_ocupable_cell(nx, ny);
		carve_passages_from(nx, ny);
	}
}

bool maze_t::adjacent_ocupable_cell_exists(unsigned x, unsigned y)
{
	unsigned nx, ny;
	for(unsigned i = dir::n; i <= dir::w; i+=2){
		nx = x;
		ny = y;
		common::coord(nx, ny, i);
		if(reachable(nx, ny) && map_.at(nx, ny) == tile::obstacle)
			if(only_one_adyacent(nx, ny))
				return true;
	}
	return false;
}

bool maze_t::only_one_adyacent(unsigned x, unsigned y)
{
	// We know (nx, ny) is reachable, now we must check if has any adyacent cells
	//  O O O
	//  O ? X
	//  O O O  Check arround ? if all are empty except X.
	unsigned counter = 0;
	unsigned nx, ny = 0;
	for(unsigned i = dir::n; i<= dir::nw; i++){
		nx = x;
		ny = y;
		common::coord(nx, ny, i);
		if(map_.at(nx, ny) == tile::empty)
			counter++;
		if(counter > 2)
			return false;
	}
	return true;
}

void maze_t::random_ocupable_cell(unsigned& x, unsigned& y)
{
	unsigned nx, ny;
	while(adjacent_ocupable_cell_exists(x, y)){
		nx = x;
		ny = y;
		unsigned dir = 0;
		if(seed_ == 0)
			dir = common::random()%4 * 2;
		else
			dir = std::rand()%4 * 2;
		common::coord(nx, ny, dir);
		if(reachable(nx, ny) && map_.at(nx, ny) == tile::obstacle){
			if(only_one_adyacent(nx, ny)){
				x = nx;
				y = ny;
				return;
			}
		}
	}
}

bool maze_t::reachable(unsigned x, unsigned y)
{
	return x >=1 && y >= 1 && x < map_.sx()-1 && y < map_.sy()-1;
}

void maze_t::set_borders(void)
{
	for(unsigned i = 0; i < map_.sx(); i++){
		map_.at(i, 0) = tile::obstacle;
		map_.at(i, map_.sy()-1) = tile::obstacle;
	}
	for(unsigned i = 0; i < map_.sy(); i++){
		map_.at(0, i) = tile::obstacle;
		map_.at(map_.sx()-1, i) = tile::obstacle;
	}
}

void maze_t::clean(void){
	map_.at(1,1) = tile::empty;
	map_.at(2,1) = tile::empty;
	map_.at(1,2) = tile::empty;
	map_.at(2,2) = tile::empty;

	map_.at(map_.sx()-2, map_.sy()-2) = tile::empty;
	map_.at(map_.sx()-3, map_.sy()-2) = tile::empty;
	map_.at(map_.sx()-2, map_.sy()-3) = tile::empty;
	map_.at(map_.sx()-3, map_.sy()-3) = tile::empty;
}

std::ostream& maze_t::print(std::ostream& os)
{
	for(unsigned i = 0; i < map_.sy(); i++){
		for(unsigned j = 0; j < map_.sx(); j++){
			switch(map_.at(j, i)){
				case 0: os << "  "; break;
				case 1: os << "██"; break;
				case 2: os << "\033[31m██\033[0m"; break;
				case 3: os << "\033[33m██\033[0m"; break;
				default: os << "??"; break;
			}
		}
		os << "\n";
	}
	return os;
}

unsigned maze_t::x(void)
{
	return map_.sx();
}

unsigned maze_t::y(void)
{
	return map_.sy();
}