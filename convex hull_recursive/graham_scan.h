//used in qsort comp function for point sorting
Point lowestPoint;
 
//qsort comp function with respect to the first point
//soriting based on the orient method
int comp(const void *p1, const void *p2)
{
   Point *point1 = (Point *)p1;
   Point *point2 = (Point *)p2;
 
   // Find orientation
   int orient = get_orientation(lowestPoint, *point1, *point2);
	
   //for same angle sorting based on distance from lower point
   if (orient == 0)
     return (get_distance(lowestPoint, *point2) >= get_distance(lowestPoint, *point1))? -1 : 1;
   return orient; 
}

// getting next to Top Point
// poping the top element, getting the 2nd top and puhing the initial top again to stack
Point getNextToTop(stack<Point> &stk)
{
    Point first = stk.top();
    stk.pop();
    Point second = stk.top();
    stk.push(first);
    return second;
}
 
//step1: finding the lowest point //in case of a tie picking the left point
//step2: place the lowest point at the top position
//step3: Sorting points with respect to the lowest point based on their polar angle.  
//		 A point p1 comes before p2 in sorted output if p2 has larger polar angle (in counterclockwise direction) than p1
//step4: Push first 3 points into the stack
//step5: Processing remaining n-3 points to get the points in the hull
//step6: Getting points in the hull means remaining points in the stack
void GrahamScan(Point points[], int n, bool isPrintOutput)
{
	
	int index;
	
	//Step1: finding the lowest point from all points
	int minY = points[0].y;
	int minPoint = 0;
	for (index = 1; index < n; index++)
	{
		int y = points[index].y;
		if ((y < minY) || minY ==  y && points[index].x < points[minPoint].x)
		{
			minY = points[index].y;
			minPoint = index;
		}
	}
 
	//step2: placing the lowest point at the top position
	swap(points[0], points[minPoint]);
 
	//step3: Sorting the points(except the lower) with respect to the lowest point based on their polar angle.
	lowestPoint = points[0];
	qsort(&points[1], n-1, sizeof(Point), comp);
	
	//step4: Placing first 3 points in stack
	stack<Point> stk;
	stk.push(points[0]);
	stk.push(points[1]);
	stk.push(points[2]);
 
	//step5: Processing remaining n-3 points to get the points in the hull
	//removing top elements until a non-left turn made
	for (index = 3; index < n; index++)
	{
		
		int orient = get_orientation(getNextToTop(stk), stk.top(), points[index]); 
		while(orient != -1)
		{
			stk.pop();
			orient = get_orientation(getNextToTop(stk), stk.top(), points[index]);
		}
		stk.push(points[index]);
	}
	
	//step6: Getting the reamining points from the stack which means the points in the hull
	if(isPrintOutput)
	{		
		printf("\nGraham Scan Algorithm\n");
		int size = stk.size();
		if(isPrintOutput)
		{
			int i=0;
			while (!stk.empty())
			{
				Point p = stk.top();
					printf("(%0.1lf,%0.1lf),",p.x, p.y);
				stk.pop();
			}
			printf("\n");
		}
		printf("Total Points in the Hull %d\n", size);
	}
	//printf("------------\n");
}
