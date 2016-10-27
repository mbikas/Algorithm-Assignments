#include "point.h"
#include "geometry.h"
#include "graham_scan.h"
#include "jarvis_march.h"


//1(d) -- testing both algorithm with given data set in question 1(d)
void testAlgorithmsWithPoints1d()
{
	printf("1(d): Testing With Data Set in 1(d)\n----------\n");
	
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;

	Point points1d[] = {	{"A", 0, 0}, {"B", -5, -2}, {"C", -2, -1}, {"D", -6, 0},
						{"E", -3.5, 1}, {"F", -4.5, 1.5}, {"G", -2.5, -5}, {"H", 1, -2.5}, {"I", 2.5, .5}, {"J", -2.2, 2.2}};
    totalPoints = sizeof(points1d)/sizeof(points1d[0]);

	printf("Input Points\n");
	for(int i=0;i<totalPoints;i++)
		printf("%s(%0.1lf,%0.1lf),",points1d[i].name, points1d[i].x, points1d[i].y);
	printf("\n");

	runTime=0.0;
	start = clock();
	GrahamScan(points1d, totalPoints, true);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(d) for GrahamScn is: %lfms\n", runTime);
			
	runTime = 0.0;
	start = clock();
	JarvisMarch(points1d, totalPoints, true);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(d) for Jarvis March is: %lfms\n", runTime);

	printf("----End of 1(d)------------\n\n");
}

//1(e) -- testing both algorithm using test data of 1000 points:  (i, i2), for i = 1 to 1000.
void testAlgorithmsWithTestDataOf1000Points()
{
	printf("\n1(e): Testing With 1000 Data Set in 1(e)\n----------\n");
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;

	Point points[MAX_POINTS];

	for (int i=0;i<1000;i++)
	{
		sprintf(points[i].name, "%d", i);
		points[i].x = (double)(i+1);
		points[i].y = (double)(i+1) * (i+1);
	}

	totalPoints = 1000;

	runTime=0.0;
	start = clock();
	GrahamScan(points, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(e) for GrahamScn is: %lfms\n", runTime);
			
	runTime = 0.0;
	start = clock();
	JarvisMarch(points, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(e) for Jarvis March is: %lfms\n", runTime);
	printf("----End of 1(e)------------\n\n");
}


//1(f) -- testing both algorithm using test data of 1000 points Plus three given points
void testAlgorithmsWithTestDataOf1000PointsPlusThree()
{
	printf("1(f): \nTesting With 1000 Data Set + 3 given points in 1(f)\n----------\n");
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;

	Point points[MAX_POINTS];

	for (int i=0;i<1000;i++)
	{
		sprintf(points[i].name, "%d", i);
		points[i].x = (double)(i+1);
		points[i].y = (double)(i+1) * (i+1);
	}
	
	//adding three given points
	sprintf(points[i].name, "%d", i);
	points[i].x = 0; points[i].y = 0;
	
	sprintf(points[i+1].name, "%d", i+1);
	points[i+1].x = 1001; points[i+1].y = 0;

	sprintf(points[i+2].name, "%d", i+2);
	points[i+2].x = 1001; points[i+2].y = 1002001;
	

	totalPoints = 1000+3;

	runTime=0.0;
	start = clock();
	GrahamScan(points, totalPoints, true);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(f) for GrahamScn is: %lfms\n", runTime);
			
	runTime = 0.0;
	start = clock();
	JarvisMarch(points, totalPoints, true);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(f) for Jarvis March is: %lfms\n", runTime);
	printf("----End of 1(f)------------\n\n");
}

 
// Driver program to test above functions
int main()
{
	freopen("output.txt","w",stdout);
	

	//1(d) -- testing both algorithm with given data set in question 1(d)
	testAlgorithmsWithPoints1d();
	///////end of 1(d)

	//1(e) -- testing both algorithm using test data of 1000 points:  (i, i2), for i = 1 to 1000.
	testAlgorithmsWithTestDataOf1000Points();
	///////end of 1(e)

	//1(f) -- testing both algorithm using test data of 1000 points Plus three given points
	testAlgorithmsWithTestDataOf1000PointsPlusThree();
	///end of 1(f)

	//1(g)
	printf("\n\n1(g)\n----------\n");
	printf("In 1(e): All the 1000 points are on the convex hull, total no of points in the hull is then 1000. ");
	printf("Grahan scan = O(nlogn) and Jarvis March = O(nh) where h = no of points in the hull. ");
	printf("So log(1000) = 3 < h = 1000, which mean for this input set graham scan algorithm should run faster. ");
	printf("The implementation above also shows the same behavior\n\n");

	printf("In 1(f) : Only the added three points are on the hull, total no of points in the hull is then 3. ");
	printf("grahan scan = O(nlogn) and Jarvis March = O(nh) where h = no of points in the hull. ");
	printf("So log(1000) = 3 == h = 3, which mean for this input set both algorithm should take approximately same time. ");
	printf("But The implementation above shows that Jarvis March runs much faster than Graham scan for this input\n");
	//end of 1(g)

	return 0;
}
