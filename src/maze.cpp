#include "maze.hpp"

maze_t::maze_t(unsigned x, unsigned y):
map_(x, y, tile::obstacle),
seed_(0),
have_seed_(false)
{}

cell_t& maze_t::at(unsigned x, unsigned y)
{
	return map_.at(x, y);
}

cell_t& maze_t::at(point_t point)
{
	return map_.at(point.x(), point.y());
}

void maze_t::generate(void)
{
	map_.clear();
	carve_passages_from(point_t(1, 1));
	clean();
}

void maze_t::generate(unsigned seed)
{
	have_seed_ = true;
	seed_ = seed*map_.x()*map_.y();
	std::srand(seed_);
	generate();
	have_seed_ = false;
}

void maze_t::carve_passages_from(point_t point)
{
	map_.at(point.x(), point.y()) = tile::empty;
	while(adjacent_ocupable_cell_exists(point))
		carve_passages_from(random_ocupable_cell(point));
}

bool maze_t::adjacent_ocupable_cell_exists(point_t point)
{
	point_t newpoint;
	for(unsigned dir = dir_t::n; dir <= dir_t::w; dir+=2){
		dir_t newdir = static_cast<dir_t>(dir);
		newpoint = point + newdir;

		if(reachable(newpoint) && (map_.at(newpoint.x(), newpoint.y()) == tile::obstacle))
			if(only_one_adyacent(newpoint, newdir))
				return true;
	}
	return false;
}

bool maze_t::only_one_adyacent(point_t point, dir_t direction)
{
	unsigned displacement = 0;
	switch(direction){
		case dir_t::n: displacement = dir_t::w; break;
		case dir_t::e: displacement = dir_t::n; break;
		case dir_t::s: displacement = dir_t::e; break;
		case dir_t::w: displacement = dir_t::s; break;
		default: break;
	}
	point_t newpoint;
	for(unsigned dir = 0; dir < 5; dir++){
		unsigned displ_dir = (dir+displacement)%8;
		dir_t newdir = static_cast<dir_t>(displ_dir);
		newpoint = point + newdir;
		if(reachable(newpoint))
			if(map_.at(newpoint.x(), newpoint.y()) == tile::empty)
				return false;
	}
	return true;
}

point_t maze_t::random_ocupable_cell(point_t point)
{
	point_t newpoint;
	while(adjacent_ocupable_cell_exists(point)){
		unsigned dir = 0;
		if(have_seed_)
			dir = std::rand()%4 * 2;
		else
			dir = common::random()%4 * 2;
		dir_t newdir = static_cast<dir_t>(dir);

		newpoint = point + newdir;

		if(reachable(newpoint) && map_.at(newpoint.x(), newpoint.y() == tile::obstacle))
			if(only_one_adyacent(newpoint, newdir))
				return newpoint;
	}
	return point_t(-1, -1); //TODO: throw exception
}

bool maze_t::reachable(point_t point)
{
	return point.x() >=1 && point.y() >= 1 && point.x() < map_.x()-1 && point.y() < map_.y()-1;
}

void maze_t::clean(void)
{
	map_.at(1,1) = tile::empty;
	map_.at(2,1) = tile::empty;
	map_.at(1,2) = tile::empty;
	map_.at(2,2) = tile::empty;

	map_.at(map_.x()-2, map_.y()-2) = tile::empty;
	map_.at(map_.x()-3, map_.y()-2) = tile::empty;
	map_.at(map_.x()-2, map_.y()-3) = tile::empty;
	map_.at(map_.x()-3, map_.y()-3) = tile::empty;
}

unsigned maze_t::x(void)
{
	return map_.x();
}

unsigned maze_t::y(void)
{
	return map_.y();
}

std::ostream& operator<<(std::ostream& os, const maze_t& maze)
{
	for(unsigned i = 0; i < maze.map_.y(); i++){
		for(unsigned j = 0; j < maze.map_.x(); j++){
			switch(maze.map_.at(j, i)){
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