//Step1: Finding the leftMost point
//Step2: Starting from leftMost point, moving counterclockwise until hit the start point again
void JarvisMarch(Point points[], int noOfPoints, bool isPrintOutput)
{
	int index;
    
	//BaseCase:	If no of points is less then 3 then all the points are in the hull
    if (noOfPoints < 3) return;
 
    //Initialization
    int hull[MAX_POINTS];
    for (index = 0; index < noOfPoints; index++)
        hull[index] = -1;
 
    //Step1: Finding the leftMost point from all the points
    int pointLeftIndex = 0;
    for (index = 0; index < noOfPoints; index++)
	{
        if (points[index].x < points[pointLeftIndex].x)
            pointLeftIndex = index;
	}

    //Step2: Starting from leftMost point, moving counterclockwise until hit the start point again
    int p1Index = pointLeftIndex, p2Index;
    do
    {
        //Searching point p2 in the hull such that orientation(p1, index, p2) is counterclockwise for all the points
        p2Index = (p1Index + 1) % noOfPoints;
        for (index = 0; index < noOfPoints; index++)
		{
			if (get_orientation(points[p1Index], points[index], points[p2Index]) == -1)//counterclockwise
				p2Index = index;
		} 
		//Adding the point p2 to the hull as the next point of p1
        hull[p1Index] = p2Index;  
        p1Index = p2Index;
    } while (p1Index != pointLeftIndex);
 
    // Print Result
	int nPoints =0;
	printf("\nJarvis Algorithm\n");
	for (index = 0; index < noOfPoints; index++)
    {
        if (hull[index] != -1)
		{
			if(isPrintOutput)
				printf("%s(%0.1lf,%0.1lf),",points[index].name, points[index].x, points[index].y);
			nPoints++;
		}
    }
	if(isPrintOutput)printf("\n");
	printf("Total Points in the Hull %d\n", nPoints);
	//printf("--------------\n");
}
