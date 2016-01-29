#include <deque>

#include "common.hpp"
#include "path.hpp"

class list_t{
private:
	std::deque<path_t> list_;
public:
	list_t(void);
	~list_t(void);

	void push_back(path_t& path);
	void push_front(path_t& path);

	path_t pop_back(void);
	path_t pop_front(void);
	path_t pop_at(unsigned index);

	void sort(void);

	friend std::ostream& operator<<(std::ostream &os, const list_t &list);
};