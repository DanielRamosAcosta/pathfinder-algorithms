#pragma once

#include <cstdlib>
#include <ctime>
#include <unistd.h>

/*
     North
       |
West  --- East
       |
     South

(0,0) (1,0) (2,0)
(0,1) (1,1) (2,1)
(0,2) (1,2) (2,2)

*/

typedef unsigned cell_t;

enum dir_t{
	n=0,
	ne=1,
	e=2,
	se=3,
	s=4,
	sw=5,
	w=6,
	nw=7,
	endEnum
};

enum tile{
	empty=0,
	obstacle=1,
	path=2,
	marked=3
};

namespace common{
	void coord(unsigned& x, unsigned& y, unsigned direction);
	unsigned random(void);
	unsigned mix(unsigned long a, unsigned long b, unsigned long c);
}