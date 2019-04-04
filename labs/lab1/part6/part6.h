#ifndef PART6_H
#define PART6_H

struct point
{
   double x;
   double y;
};

struct rectangle
{
	struct point top_left;
	struct point bottom_right;
};

struct point create_point(double x, double y);

int is_a_square(struct rectangle r1);

#endif
