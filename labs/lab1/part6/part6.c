#include "part6.h"

struct point create_point(double x, double y)
{
   struct point p;

   p.x = x;
   p.y = y;

   return p;
}
int is_a_square(struct rectangle r1)
{
	if ((r1.top_left.x - r1.bottom_right.x) == (r1.top_left.y - r1.bottom_right.y))
		return 0;
	else
		return 1;
}
