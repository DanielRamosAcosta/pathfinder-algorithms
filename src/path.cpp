#include "path.hpp"

path_t::path_t(void):
	start_(nullptr),
	end_(nullptr),
	cost_(0)
{}

path_t::~path_t(void)
{
	clean();
}

path_t::path_t(const path_t& other):
	start_(nullptr),
	end_(nullptr),
	cost_(0)
{
	node_t* ptr = other.start_;
	while(ptr != nullptr){
		push(ptr->point());
		ptr = ptr->next();
	}
}

void path_t::clean(void)
{
	node_t* ptr = start_;
	while(start_ != nullptr){
		start_ = start_->next();
		delete ptr;
		ptr = start_;
	}
	start_ = nullptr;
	end_ = nullptr;
}

void path_t::push(point_t point)
{
	if(start_ == nullptr)
		start_ = end_ = new node_t(point);
	else{
		end_->next() = new node_t(point);
		end_ = end_->next();
	}
}

point_t& path_t::last(void)
{
	// TODO: throw exception if list is empty
	// if(end_ == nullptr)
	// 	throw ????
	return end_->point();
}

point_t& path_t::operator[](unsigned index)
{
	node_t* ptr = start_;
	unsigned it = 0;
	while(it != index && ptr != nullptr){
		it++;
		ptr = ptr->next();
	}
	// TODO: operator[] throw excpetion if error in index
	// if(ptr == nullptr)
	// 	throw ????
	return ptr->point();
}

path_t& path_t::operator=(const path_t& other)
{
	clean();
	node_t* ptr = other.start_;
	while(ptr != nullptr){
		push(ptr->point());
		ptr = ptr->next();
	}
	return *this;
}

unsigned path_t::size(void)
{
	unsigned sz = 0;
	node_t* ptr = start_;
	while(ptr != nullptr){
		sz++;
		ptr = ptr->next();
	}
	return sz;
}

unsigned& path_t::cost(void)
{
	return cost_;
}

unsigned path_t::acumulated_cost(void)
{
	unsigned cost = 0;
	node_t* ptr = start_;
	while(ptr != nullptr){
		cost += ptr->cost();
		ptr = ptr->next();
	}
	return cost;
}

bool path_t::is(const point_t& point)
{
	node_t* ptr = start_;
	while(ptr != nullptr){
		if(ptr->point() == point)
			return true;
		ptr = ptr->next();
	}
	return false;
}

bool path_t::operator==(path_t& other)
{
	return last() == other.last();
}

bool path_t::operator!=(path_t& other)
{
	return last() != other.last();
}

bool path_t::operator<(path_t& other)
{
	return cost_ < other.cost_;
}

bool path_t::operator<=(path_t& other)
{
	return cost_ < other.cost_;
}

bool path_t::operator>(path_t& other)
{
	return cost_ < other.cost_;
}

bool path_t::operator>=(path_t& other)
{
	return cost_ < other.cost_;
}


std::ostream& operator<<(std::ostream& os, const path_t& path){
	node_t* ptr = path.start_;
	bool first = true;

	while(ptr != nullptr){
		if(first){
			os << ptr->point();
			first = false;
		}
		else
			os  << "->" << ptr->point();
		ptr = ptr->next();
	}
	return os;
}