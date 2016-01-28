#pragma once

#include "common.hpp"
#include "node.hpp"

class path_t{
private:
	node_t* start_;
	node_t* end_;
	std::size_t sz_;
public:
	path_t(void);
	~path_t(void);
	void push(point_t point);
	point_t& last(void);
	point_t& operator[](unsigned index);
};