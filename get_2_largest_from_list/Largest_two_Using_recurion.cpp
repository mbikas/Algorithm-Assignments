#include <stdio.h>

#define SWAP(x,y) x ^= y, y ^= x, x ^= y


/*	get two maximum number from a staring index of an array using recursion
	input 
	a[]  array ofnumbers
	max1 pointer of 1st maxumum number
	max2 pointer of 2nd maximum number
	cIndex starting index
	n sixe of the array
*/	
void getFirstTwoMaxNumberUsingRecursion (int a[], int* max1, int* max2, int cIndex, int n) 
{
	if (cIndex == n-1)	return;	
	if (a[cIndex] >= *max1)
	{
		*max2 = *max1;
		*max1 = a[cIndex];
	}	
	else if (a[cIndex] > *max2)	*max2 = a[cIndex];
	getFirstTwoMaxNumberUsingRecursion (a, max1, max2, cIndex +1, n);
}

////////
//used for storing first two max number
int m1,m2;
/*	get two maximum number from a staring index to the end of the array using iteration */
void getFirstTwoMaxNumberUsingIteration(int a[], int n)
{	
	//initializing with the a[2] value
	int i;
	m1=0, m2=0;
	for (i=2;i < n;i++)
	{
		if (a[i] >= m1)
		{
			m2 = m1;
			m1 = a[i];
		}	
		else if (a[i] > m2)	m2 = a[i];	
	}
}

int main () 
{
	int a [] = {30, 4, 2, 15, 8, 1, 9, 12, 7, 11};
	int max1 = a[2];
	int max2 = a[2];
	int temp;

	//getting first two max number from index 3 to n using recursion
	getFirstTwoMaxNumberUsingRecursion (a, &max1, &max2, 3, 10);
	printf ("Max1 : %d, Max2: %d\n", max1, max2);

	//getting first two max number from index 3 to n using iteration
	getFirstTwoMaxNumberUsingIteration (a, 10);
	max1 = m1; max2 = m2;
	printf ("Max1 : %d, Max2: %d\n", max1, max2);


	//doing three comparison using the first two values of the list
	int cmax = (a[0] > a[1]) ? a[0]	: a[1];
	max2 = (max2 > cmax) ? max2 : cmax;
	if(max2>max1) SWAP(max2, max1);

	printf ("Max1 : %d, Max2: %d\n", max1, max2);

	return 0;
}