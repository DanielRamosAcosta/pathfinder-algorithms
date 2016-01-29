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

bool point_t::operator!=(point_t point)
{
	return x_!=point.x() || y_ != point.y();
}

point_t point_t::operator+(dir direction)
{
	point_t new_point(x_, y_);
	switch(direction){
		case dir::n:	new_point.y_-=1;					break;
		case dir::ne:	new_point.y_-=1; new_point.x_+=1;	break;
		case dir::e:	new_point.x_+=1;					break;
		case dir::se:	new_point.y_+=1; new_point.x_+=1;	break;
		case dir::s:	new_point.y_+=1;					break;
		case dir::sw:	new_point.y_+=1; new_point.x_-=1;	break;
		case dir::w:	new_point.x_-=1;					break;
		case dir::nw:	new_point.y_-=1; new_point.x_-=1;	break;
		case dir::endEnum: break;
	}
	return new_point;
}

std::ostream& operator<<(std::ostream& os, const point_t& point){
	os << "(" << point.x_ << ", " << point.y_ << ")";
	return os;
}