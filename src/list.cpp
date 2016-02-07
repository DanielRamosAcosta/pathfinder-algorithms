#include "list.hpp"

list_t::list_t(void)
{}

list_t::~list_t(void)
{}


void list_t::push_back(const path_t& path)
{
	list_.push_back(path);
}

void list_t::push_front(const path_t& path)
{
	list_.push_front(path);
}


path_t list_t::pop_back(void)
{
	path_t old = list_.back();
	list_.pop_back();
	return old;
}

path_t list_t::pop_front(void)
{
	path_t old = list_.front();
	list_.pop_front();
	return old;
}

path_t list_t::pop_at(const unsigned index)
{
	path_t algo;
	return algo; //TODO
}

path_t& list_t::front(void)
{
	return list_.front();
}

void list_t::sort(void)
{
	for(std::size_t i = 0; i < list_.size(); i++){
		std::size_t min = i;
		for(std::size_t j = i + 1; j < list_.size(); j++)
			if(list_[j].cost() < list_[min].cost())
				min = j;
		std::swap(list_[i], list_[min]);
	}
}

bool list_t::empty(void)
{
	return list_.empty();
}

unsigned list_t::size(void)
{
	return list_.size();
}

path_t& list_t::operator[](const unsigned index)
{
	return list_[index];
}

std::ostream& operator<<(std::ostream& os, const list_t& list)
{
	for(auto &i: list.list_)
		os << i << std::endl;
	return os;
}