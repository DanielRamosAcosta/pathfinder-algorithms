#include "node.hpp"

node_t::node_t(void):
	next_(nullptr),
	prev_(nullptr),
	point_(0,0)
{}

node_t::node_t(point_t point):
	next_(nullptr),
	prev_(nullptr),
	point_(point)
{

}

node_t::~node_t(void)
{}

point_t& node_t::point(void)
{
	return point_;
}

node_t*& node_t::next(void)
{
	return next_;
}

node_t*& node_t::prev(void)
{
	return prev_;
}