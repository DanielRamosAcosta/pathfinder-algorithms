#pragma once

#include "common.hpp"
#include "point.hpp"

class node_t{
private:
	node_t* next_;
	point_t point_;
	unsigned cost_;
public:
	node_t(void);
	node_t(point_t point);
	node_t(point_t point, unsigned cost);
	~node_t(void);
	node_t*& next(void);
	point_t& point(void);
	unsigned& cost(void);
};