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
void swap(Point &point1, Point &point2)
{
    Point tempPoint = point1;
    point1 = point2;
    point2 = tempPoint;
}

//checking if two double values are equal or not
bool equals(double x, double y)
{
	return fabs(x - y) <= EPSILON ;
}

//checking if two points are equal or not
bool equals(Point p1, Point p2)
{
	return(fabs(p1.x - p2.x) <= EPSILON && fabs(p1.y - p2.y) <= EPSILON);
}


