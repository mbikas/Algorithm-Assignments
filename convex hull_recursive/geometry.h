#define PI 3.1415926535897932384
#define EPSILON 1e-10

//return distance between Point a and Point b
double get_distance(Point a, Point b)
{
	return sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
}

//return 1 is a->b to a->c is clockwies, -1 anticlockwiew, 0 same line
int get_orientation(Point a, Point b, Point c)
{
	double  val1 = (c.x - a.x) * (b.y - a.y);
	double val2 = (c.y - a.y) * (b.x - a.x);
	if (val1 > val2) return 1;
	if (val1 < val2) return -1;
	return 0;
}

//swapping two point
void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

bool equalsDouble(double x, double y)
{
	return fabs(x - y) <= EPSILON ;
}

