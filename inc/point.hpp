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
	unsigned x(void) const;
	unsigned y(void) const;
	bool operator==(const point_t&) const;
	bool operator!=(const point_t&) const;

	point_t operator+(const dir_t&) const;

	friend std::ostream& operator<<(std::ostream&, const point_t&);
};