#pragma once

#include "common.hpp"
#include "point.hpp"

class node_t{
private:
	node_t* next_;
	node_t* prev_;
	point_t point_;
public:
	node_t(void);
	node_t(point_t point);
	~node_t(void);
	point_t& point(void);
	node_t*& next(void);
	node_t*& prev(void);
};