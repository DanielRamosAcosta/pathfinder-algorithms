#include "common.hpp"

namespace common{

	void coord(unsigned& x, unsigned& y, unsigned direction)
	{
		switch(direction){
			case dir::n:	y-=1;		break;
			case dir::ne:	y-=1; x+=1;	break;
			case dir::e:	x+=1;		break;
			case dir::se:	y+=1; x+=1;	break;
			case dir::s:	y+=1;		break;
			case dir::sw:	y+=1; x-=1;	break;
			case dir::w:	x-=1;		break;
			case dir::nw:	y-=1; x-=1;	break;
		}
	}

	unsigned random(void)
	{
		std::srand(mix(clock(), time(NULL), getpid()));
		return std::rand();
	}

	unsigned mix(unsigned long a, unsigned long b, unsigned long c)
	{
		a=a-b;  a=a-c;  a=a^(c >> 13);
		b=b-c;  b=b-a;  b=b^(a << 8);
		c=c-a;  c=c-b;  c=c^(b >> 13);
		a=a-b;  a=a-c;  a=a^(c >> 12);
		b=b-c;  b=b-a;  b=b^(a << 16);
		c=c-a;  c=c-b;  c=c^(b >> 5);
		a=a-b;  a=a-c;  a=a^(c >> 3);
		b=b-c;  b=b-a;  b=b^(a << 10);
		c=c-a;  c=c-b;  c=c^(b >> 15);
		return c;
	}

}