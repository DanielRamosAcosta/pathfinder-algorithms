#include "point.hpp"

point_t::point_t(void):
x_(0),
y_(0)
{}

point_t::point_t(unsigned x, unsigned y):
x_(x),
y_(y)
{}

unsigned& point_t::x(void)
{
	return x_;
}

unsigned& point_t::y(void)
{
	return y_;
}

bool point_t::operator==(point_t point)
{
	return x_==point.x() && y_ == point.y();
}

std::ostream& operator<<(std::ostream& os, const point_t& point){
	os << "(" << point.x_ << ", " << point.y_ << ")";
	return os;
}