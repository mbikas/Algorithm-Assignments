#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y) x ^= y, y ^= x, x ^= y
#define MAX_ARRAY_SIZE 131072

void generate_random_numbers(int n, char* filename)
{
	int random_number,i;
	srand(time(NULL));	
	FILE *fp = fopen(filename,"w");
	if (fp== NULL) {
		printf("Error in opening a %s\n", filename);
		return;
	}
	for (i=0;i<n;i++)
	{
		random_number = rand();
		fprintf(fp,"%d ",random_number);
	}
	fclose(fp);
}

struct maxPair
{
  int max1;
  int max2;
};


/*	get two maximum number from a staring index of an array using recursion
	input 
	a[]  array ofnumbers
	max1 pointer of 1st maxumum number
	max2 pointer of 2nd maximum number
	cIndex starting index
	n sixe of the array
*/	
void getFirstTwoMaxNumber (int a[], int* max1, int* max2, int cIndex, int n) 
{
	if (cIndex == n-1)	return;	
	
	if (a[cIndex] >= *max1)
	{
		*max2 = *max1;
		*max1 = a[cIndex];
	}	
	else if (a[cIndex] > *max2)	*max2 = a[cIndex];
	getFirstTwoMaxNumber (a, max1, max2, cIndex +1, n);
}

void getFirstTwoMaxNumberUsing3nBy2(int a[], int* max1, int* max2, int n)
{
	*max1 = a[2];
	*max2 = a[2];
	
	//getting first two max number from index 3 to n
	getFirstTwoMaxNumber (a, max1, max2, 3, n);
	//printf ("Max1 : %d, Max2: %d\n", max1, max2);

	//doing three comparison using the first two values of the list
	int cmax = (a[0] > a[1]) ? a[0]	: a[1];
	*max2 = (*max2 > cmax) ? *max2 : cmax;
	if(*max2>*max1) SWAP(*max2, *max1);
	//printf ("Max1 : %d, Max2: %d\n", *max1, *max2);
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


int maxIndexes[MAX_ARRAY_SIZE]; // to store the maxIndexes 
typedef struct
{
	int value;
	int preMax[20];
	int size;
}number;
number numbers[MAX_ARRAY_SIZE];

int getSecondMax()
{
	int secondMax=0, i;

	for (i=0;i<numbers[maxIndexes[0]].size;i++)
	{
		if(numbers[maxIndexes[0]].preMax[i] > secondMax) secondMax = numbers[maxIndexes[0]].preMax[i];
	}
	return secondMax;
}



void initialize(int a[], int size)
{
	int i,cMaxIndex, cMinIndex;
	int index = 0;
	for (i=0;i<size;i+=2)
	{
		if(a[i]>a[i+1])
		{
			cMaxIndex = i;
			cMinIndex = i+1;
		}
		else
		{
			cMaxIndex = i+1;
			cMinIndex = i;
		}
		
		numbers[index].value = a[cMaxIndex];
		numbers[index].preMax[0] = a[cMinIndex];
		numbers[index].size = 1;
		maxIndexes[index] = index;
		index++;
		
	}
}

//initially maxIndexes have all the indexex 0 to n-1
//in each interation it will decrease by half
//for simplisity assuming that size will always be power of two		
void calculateTwoMaxUsingTournamentMethod(int size)
{
	
	int i; //variable used for loop
	int index; //variable starts from 0 in each iteration to store current max indexes
	int cMaxIndex; //holds current max index in each iteration
	int cMinIndex; //holds current min index in each iteration	

	int count = size; //temporary variable to hold size
	
	while(count > 1)
	{		
		index = 0; 
		for (i=0;i<count;i+=2)
		{			
			if(numbers[maxIndexes[i]].value>numbers[maxIndexes[i+1]].value){
				cMaxIndex = maxIndexes[i];
				cMinIndex = maxIndexes[i+1];
			}
			else{
				cMaxIndex = maxIndexes[i+1];
				cMinIndex = maxIndexes[i];
			}
			
			maxIndexes[index] = cMaxIndex;
			numbers[cMaxIndex].preMax[numbers[cMaxIndex].size++] = numbers[cMinIndex].value;
			index++;
			//printf("CMAX:%d ",cMaxIndex);

		}
		count = index;
		//printf("\nCOUNT:%d\n",count);
	}	
}

int main()
{
	int val, total,i;
	int a[MAX_ARRAY_SIZE];

	int size [5] = {16, 128, 1024, 16384, 131072};
	char *fileNames[5] = { "16.txt", "128.txt", "1024.txt", "16384.txt", "131072.txt"};


	for(i=0;i<5;i++)
		generate_random_numbers(size[i], fileNames[i]);	
	//freopen("out.txt","wt",stdout);
	for(i=0;i<5;i++)
	{
		freopen(fileNames[i],"r",stdin);
		total=0;
		while(scanf("%d",&val)==1)
		{
			a[total++] = val;
		}
		int max1, max2;
		clock_t start, end;
		double runTime=0.0;
		
		printf("Total Number:%d\n",total);
		start = clock();
		m1 = m2 = 0;
		getFirstTwoMaxNumberUsingIteration(a, total);
		end = clock();
		runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
		printf("Recursive 3n/2 Algorithm: Max1:%d  Max2:%d RunTime:%lfms\n",m1, m2,runTime);
				
		
		start = clock();	
		initialize(a, total);
		calculateTwoMaxUsingTournamentMethod(total);
		max1 = numbers[maxIndexes[0]].value;
		max2 = getSecondMax();
		end = clock();
		runTime = (end - start) / (double) (CLOCKS_PER_SEC);
		printf("Tournament Method: Max1:%d  Max2:%d RunTime:%lfms\n",max1,max2, runTime);

	}


	
	return 0;

}
