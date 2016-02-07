#pragma once

#include <iostream>

#include "common.hpp"
#include "node.hpp"

class path_t{
private:
	node_t* start_;
	node_t* end_;
	double cost_;
public:
	path_t(void);
	~path_t(void);
	path_t(const path_t&);
	void clean(void);

	void push(const point_t);
	point_t& last(void);
	point_t last(void) const;
	point_t& operator[](const unsigned);
	path_t& operator=(const path_t&);

	unsigned size(void) const;
	double& cost(void);
	double acumulated_cost(void) const;

	bool is(const point_t&);

	bool operator==(const path_t&) const;
	bool operator!=(const path_t&) const;
	bool operator<(const path_t&) const;
	bool operator<=(const path_t&) const;
	bool operator>(const path_t&) const;
	bool operator>=(const path_t&) const;

	friend std::ostream& operator<<(std::ostream&, const path_t&);
};