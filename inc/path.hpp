#pragma once

#include <iostream>

#include "common.hpp"
#include "node.hpp"

class path_t{
private:
	node_t* start_;
	node_t* end_;
public:
	path_t(void);
	~path_t(void);
	void push(point_t point);
	point_t& last(void);
	point_t& operator[](unsigned index);

	unsigned acumulated_cost(void);

	friend std::ostream& operator<<(std::ostream &os, const path_t &path);
};