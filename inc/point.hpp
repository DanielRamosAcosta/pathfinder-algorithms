#pragma once

class point_t{
private:
	unsigned x_;
	unsigned y_;
public:
	point_t(void);
	point_t(unsigned x, unsigned y);
	unsigned& x(void);
	unsigned& y(void);
};