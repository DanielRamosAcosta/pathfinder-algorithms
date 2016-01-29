#pragma once

#include <iostream>

#include "common.hpp"
#include "node.hpp"

class path_t{
private:
	node_t* start_;
	node_t* end_;
	unsigned cost_;
public:
	path_t(void);
	~path_t(void);
	path_t(const path_t& other);
	void clean(void);

	void push(point_t point);
	point_t& last(void);
	point_t& operator[](unsigned index);
	path_t& operator=(const path_t& other);

	unsigned size(void);
	unsigned& cost(void);
	unsigned acumulated_cost(void);

	bool is(const point_t& point);

	bool operator==(path_t& other);
	bool operator!=(path_t& other);
	bool operator<(path_t& other);
	bool operator<=(path_t& other);
	bool operator>(path_t& other);
	bool operator>=(path_t& other);

	friend std::ostream& operator<<(std::ostream &os, const path_t &path);
};