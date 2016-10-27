#include "point.h"
#include "geometry.h"
#include "graham_scan.h"
#include "jarvis_march.h"
#include "merge_hull.h"


//1(d) -- testing both algorithm with given data set in question 1(d)
void testAlgorithmsWithPoints1d()
{
	printf("Testing and Comparing MergeHull With Data Set of Problem 1(d)\n----------\n");
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;
	
	Point points1e[] = {	{0, 0}, { -5, -2}, { -2, -1}, { -6, 0},
	{ -3.5, 1}, { -4.5, 1.5}, {  -2.5, -5}, { 1, -2.5}, {  2.5, .5}, { -2.2, 2.2}};
    totalPoints = sizeof(points1e)/sizeof(points1e[0]);
	
	runTime = 0.0;
	start = clock();
	MergeHull(points1e, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(d) for Merge Hull is: %lfms\n", runTime);

	
	runTime=0.0;
	start = clock();
	GrahamScan(points1e, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(d) for GrahamScn is: %lfms\n", runTime);
			
	runTime = 0.0;
	start = clock();
	JarvisMarch(points1e, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(d) for Jarvis March is: %lfms\n", runTime);


	printf("---------------\n\n");
}

//1(e) -- testing both algorithm using test data of 1000 points:  (i, i2), for i = 1 to 1000.
void testAlgorithmsWithTestDataOf1000Points()
{
	printf("\nTesting and Comparing MergeHull With 1000 Data Set in 1(e)\n----------\n");
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;

	Point points[MAX_POINTS];

	for (int i=0;i<1000;i++)
	{
		points[i].x = (double)(i+1);
		points[i].y = (double)(i+1) * (i+1);
	}

	totalPoints = 1000;

	runTime = 0.0;
	start = clock();
	MergeHull(points, totalPoints, false);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(e) for Merge Hull is: %lfms\n", runTime);


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
	printf("-----------\n\n");
}


//1(f) -- testing both algorithm using test data of 1000 points Plus three given points
void testAlgorithmsWithTestDataOf1000PointsPlusThree()
{
	printf("\nTesting and Comparing MergeHull With 1000 Data Set + 3 given points in 1(f)\n----------\n");
	clock_t start, end;
	double runTime=0.0;
	int totalPoints;

	Point points[MAX_POINTS];

	for (int i=0;i<1000;i++)
	{
		points[i].x = (double)(i+1);
		points[i].y = (double)(i+1) * (i+1);
	}
	
	//adding three given points
	points[i].x = 0; points[i].y = 0;
	points[i+1].x = 1001; points[i+1].y = 0;
	points[i+2].x = 1001; points[i+2].y = 1002001;
	

	totalPoints = 1000+3;

	runTime = 0.0;
	start = clock();
	MergeHull(points, totalPoints, true);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime with dataset in 1(f) for Merge Hull is: %lfms\n", runTime);


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
	printf("--------------\n\n");
}




int main()
{

	freopen("output.txt","w",stdout);
		
	//2(b) 2(c)
	//testing Merge Hull with given data set in question 1(d)
	//also comparing with Graham Scan and Jarvis March
	testAlgorithmsWithPoints1d();
	
	//testing Merge Hull using test data of 1000 points:  (i, i2), for i = 1 to 1000.
	//also comparing with Graham Scan and Jarvis March
	testAlgorithmsWithTestDataOf1000Points();
	
	//testing Merge Hull with using test data of 1000 points Plus three given points
	//also comparing with Graham Scan and Jarvis March
	testAlgorithmsWithTestDataOf1000PointsPlusThree();
	///end of 2(b) 2(c)

	return 0;
}


