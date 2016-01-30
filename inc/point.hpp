#pragma once

#include <iostream>

#include "common.hpp"

class point_t{
private:
	unsigned x_;
	unsigned y_;
public:
	point_t(void);
	point_t(unsigned x, unsigned y);
	unsigned& x(void);
	unsigned& y(void);
	bool operator==(point_t);
	bool operator!=(point_t);

	point_t operator+(dir_t direction);

	friend std::ostream& operator<<(std::ostream &os, const point_t &point);
};