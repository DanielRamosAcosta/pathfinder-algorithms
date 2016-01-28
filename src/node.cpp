#include "node.hpp"

node_t::node_t(void):
	next_(nullptr),
	point_(0,0),
	cost_(1)
{}

node_t::node_t(point_t point):
	next_(nullptr),
	point_(point),
	cost_(1)
{}

node_t::node_t(point_t point, unsigned cost):
	next_(nullptr),
	point_(point),
	cost_(cost)
{}

node_t::~node_t(void)
{}

node_t*& node_t::next(void)
{
	return next_;
}

point_t& node_t::point(void)
{
	return point_;
}

unsigned& node_t::cost(void)
{
	return cost_;
}