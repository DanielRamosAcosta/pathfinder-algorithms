#include "path.hpp"

path_t::path_t(void):
	start_(nullptr),
	end_(nullptr)
{}

path_t::~path_t(void)
{
	node_t* ptr = start_;
	while(ptr != nullptr){
		start_ = start_->next();
		delete ptr;
		ptr = start_;
	}
	start_ = nullptr;
	end_ = nullptr;
}

void path_t::push(point_t point)
{
	if(end_ == nullptr){
		start_ = end_ = new node_t(point);
	}
	else{
		end_->next() = new node_t(point);
		end_ = end_->next();
	}
}

point_t& path_t::last(void)
{
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
	// TODO:
	// if(ptr == nullptr)
	// 	throw ????
	return ptr->point();
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