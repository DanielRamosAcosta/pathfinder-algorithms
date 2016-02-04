#pragma once

#include <deque>

#include "common.hpp"
#include "path.hpp"

class list_t{
private:
	std::deque<path_t> list_;
public:
	list_t(void);
	~list_t(void);

	void push_back(const path_t&);
	void push_front(const path_t&);

	path_t pop_back(void);
	path_t pop_front(void);
	path_t pop_at(const unsigned);

	path_t& front(void);

	void sort(void);
	bool empty(void);

	friend std::ostream& operator<<(std::ostream& , const list_t&);
};