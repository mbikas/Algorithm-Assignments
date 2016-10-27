#include "cdll.h"
//#include "geometry.h"

typedef struct{
	vector<char> name;
    vector<double> xCordinates;
    vector<double> yCordinates;
}Hull;

//qsort compare function with respect to the first point
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
 
   //returning 1,-1,0 based on x value
   double xDifference = p1->x - p2->x;
   if(xDifference > 0) return 1;
   if(xDifference < 0) return -1;
   return 0;
}

//not used in here
void bubble_sort(Point points[], int totalPoints) 
{
        for(int i = 0; i < totalPoints; i++) 
		{
            for(int j = 0; j < i; j++) 
			{
                if(points[i].x < points[j].x ) 
				{
                    double temp = points[i].x;
                    points[i].x = points[j].x ;
                    points[j].x = temp;
                    double temp2 = points[i].y;
                    points[i].y = points[j].y;
                    points[j].y = temp2;
                }
            }
        }
}
double equation(double x1, double x2, double y1, double y2, double x, double y)
{
    return ((y-y1) * (x1-x2)) - ((y1-y2)*(x-x1));
}

bool check(Point l, Point r, Hull left, Hull right)
{
	int i;
    bool f;
    double tempo1 = left.xCordinates[0];
    double tempo2 = left.yCordinates[0];
    for (i = 0; i < left.xCordinates.size(); i++)
    {
		if(equalsDouble(tempo1,  l.x) && equalsDouble(tempo2 ,l.y) )
        {
            tempo1 = left.xCordinates[i];
            tempo2 = left.yCordinates[i];
        }
        else	break;
    }
    if (equation(l.x, r.x, l.y, r.y, tempo1, tempo2) < 0)
        f = false;
    else
		f = true;

	for (i = 0; i < left.xCordinates.size(); i++)
	{
		if (equation(l.x, r.x, l.y, r.y, left.xCordinates[i], left.yCordinates[i]) > 0 && f == false)
			return false;
        else if (equation(l.x, r.x, l.y, r.y, left.xCordinates[i], left.yCordinates[i]) < 0 && f == true)
            return false;
	}
		
    for(i = 0; i < right.xCordinates.size(); i++ )
    {
		if (equation(l.x, r.x, l.y, r.y, right.xCordinates[i], right.yCordinates[i]) > 0 && f == false)
			return false;
        else if (equation(l.x, r.x, l.y, r.y, right.xCordinates[i], right.yCordinates[i]) < 0 && f == true)
			return false;
	}
    return true;
}

//this merge function is taken from
//http://basicodingfordummies.blogspot.com/2013/03/2d-convex-hull-in-c-using-divide-and.html
Hull merge(Hull left, Hull right)
{
	//circular double link list
	cdll l, r;
    int counter_l, counter_r;
    node *n1, *n2, *n3, *n4;
    
	Hull final;
	
    l.insert(left.xCordinates , left.yCordinates);
    r.insert(right.xCordinates, right.yCordinates);
    int flag = 0;
    Point temp1, temp2;
    l.pointer = l.y_max();
    r.pointer = r.y_max();
    if(l.y_max()->data2 > r.y_max()->data2)
    {
		counter_l = 0;
        while (counter_l != l.size())
        {
			counter_l++;
            counter_r=0;
            r.pointer = r.y_max();
            while (counter_r != r.size()) 
			{
                counter_r++;
                temp1.x = l.pointer->data;
                temp1.y = l.pointer->data2;
                temp2.x = r.pointer->data;
                temp2.y = r.pointer->data2;
                
				bool b1 = check(temp1 , temp2 , left , right );
                if(b1)
                {
					n1 = l.pointer;
                    n2 = r.pointer;
                    flag = 1;
                    break;
                }
                else	
					r.pointer = r.pointer->prev;
			}
            if(flag == 1)
                 break;
            l.pointer = l.pointer->next;
        }
    }
    else
	{
		counter_r = 0;
        while (counter_r != r.size()) 
		{
			counter_r++;
            counter_l=0;
            l.pointer = l.y_max();
            while (counter_l != l.size())
            {
				counter_l++;
                temp1.x = l.pointer->data;
                temp1.y = l.pointer->data2;
                temp2.x = r.pointer->data;
				temp2.y = r.pointer->data2;
                bool b1 = check(temp1, temp2, left, right);
                if(b1)
                {
					n1 = l.pointer;
                    n2 = r.pointer;
                    flag = 1;
                    break;
                }
                else
					l.pointer = l.pointer->next;
            }
            if(flag == 1)
				break;
            r.pointer = r.pointer->prev;
        }
    }
    
	//Finding Lower Tangent
    l.pointer = l.y_min() ;
    r.pointer = r.y_min() ;
    flag = 0;
    
	if(l.y_min()->data2 < r.y_min()->data2)
    {
		counter_l = 0;
        while (counter_l != l.size()) 
		{
            counter_l++;
            counter_r=0;
            r.pointer = r.y_max();
            while (counter_r != r.size()) 
			{
                counter_r++;
                temp1.x = l.pointer->data;
                temp1.y = l.pointer->data2;
                temp2.x = r.pointer->data;
                temp2.y = r.pointer->data2;
                bool b1 = check(temp1, temp2, left, right);
                if(b1)
                {
					n3 = l.pointer;
                    n4 = r.pointer;
                    flag = 1;
                    break;
                }
                else	r.pointer = r.pointer->next;
            }
            if(flag == 1)
                break;
            l.pointer = l.pointer->prev;
        }
    }
    else
    {
		counter_r = 0;
        while (counter_r != r.size())
        {
			counter_r++;
            counter_l=0;
			l.pointer = l.y_max();
            while (counter_l != l.size())
            {
				counter_l++;
                Point temp1, temp2;
                temp1.x = r.pointer->data;
                temp1.y = r.pointer->data2;
                temp2.x = l.pointer->data;
                temp2.y = l.pointer->data2;
                bool b1 = check(temp1, temp2, left, right);
                if(b1)
                {
					n3 = l.pointer;
                    n4 = r.pointer;
                    flag = 1;
                    break;
				}
                else
					l.pointer = l.pointer->prev;
			}
            if(flag == 1)
				break;
			r.pointer = r.pointer->next;
		}
	}

	//Combination
    node* tempr1 = n2;
    while (tempr1 != n4)
    {
        final.xCordinates.push_back(tempr1->data);
		final.yCordinates.push_back(tempr1->data2);
        tempr1 = tempr1->next;
    }
    final.xCordinates.push_back(tempr1->data);
    final.yCordinates.push_back(tempr1->data2);
    node*  tempr2 = n3;
    while(tempr2 != n1)
    {
		final.xCordinates.push_back(tempr2->data);
        final.yCordinates.push_back(tempr2->data2);
        tempr2 = tempr2->next;
    }
       
    final.xCordinates.push_back(tempr2->data);
    final.yCordinates.push_back(tempr2->data2);
    return final;
}

//divide the points into two halved recursively like mergesort
//then merge the two hull
Hull Split(Point points[], int start, int end, int totalPoints)
{
	int i;
	
	//Base cases if total points is less than 4
    if(totalPoints <= 3 || equalsDouble(points[start].x,points[end].x)==true )
	{
        Hull hull;
        if(equalsDouble(points[start].x,points[end].x))
        {
            hull.xCordinates.push_back(points[start].x);
            hull.yCordinates.push_back(points[start].y);
            hull.xCordinates.push_back(points[end].x);
            hull.yCordinates.push_back(points[end].y);
        }
        else
        {
            for(i = start; i <= end; i++)
            {
                hull.xCordinates.push_back (points[i].x);
                hull.yCordinates.push_back (points[i].y);
            }
        }
        return hull;
    }
        
	int mid = (start + end)/2;
    Hull leftHull;
    Hull rightHull;
    leftHull = Split(points, start, mid, mid - start + 1);
    rightHull = Split(points, mid + 1, end, end - mid);
    Hull mergedHull = merge(leftHull, rightHull);
    return mergedHull;
}

void printHull(Hull hull) 
{
	printf("Merge Hull Algorithm\n");
	vector<double> x = hull.xCordinates;
	vector<double> y = hull.yCordinates;
    for(int i = 0; i < x.size(); i++ ) 
	{
        //cout << x[i] << " " << y[i] << endl;
        cout << "(" << x[i] << ", " << y[i] <<") , ";
    }
    cout << endl;
    printf("Total Points in the Hull %d\n", x.size());
}


//sort the points based on x coordinates
//split into half and recursively calculate the hull
//merge the hull
void MergeHull(Point points[], int totalPoints, bool isPrintOutput)
{
	//sort_first(points, totalPoints);
	qsort(points, totalPoints, sizeof(Point), compare);
    Hull hull = Split(points, 0, totalPoints-1, totalPoints);
    if(isPrintOutput)	printHull(hull);
}

//Comments: 
//The divide and conquer version of the code is adapted from the below source
//http://basicodingfordummies.blogspot.com/2013/03/2d-convex-hull-in-c-using-divide-and.html
