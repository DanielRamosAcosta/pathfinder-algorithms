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

point_t& path_t::last(void)
{
	return end_->point();
}

point_t& path_t::operator[](unsigned index)
{
	if(index >= sz_)
		exit(1);//TODO: throw exception

	node_t* ptr = nullptr;
	if(index/2 < sz_/2){
		unsigned it = 0;
		ptr = start_;
		while(it != index){
			it++;
			ptr = ptr->next();
		}
	}
	else{
		unsigned it = sz_-1;
		while(it != index){
			it--;
			ptr = ptr->prev();
		}
	}
	return ptr->point();
}