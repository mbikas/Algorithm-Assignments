#include <stdio.h>

#define MAX_ARRAY_SIZE 100
#define SWAP(x,y) x ^= y, y ^= x, x ^= y

//numbers to compare
int num[] = {16, 13, 15, 19, 8, 21, 4, 7};
int size_total = 8;
int maxIndexes[MAX_ARRAY_SIZE]; // to store the maxIndexes 

typedef struct
{
	int value;
	int preMax[MAX_ARRAY_SIZE];
	int size;
}number;
number numbers[MAX_ARRAY_SIZE];

void initialize(int size)
{
	int i;
	for (i=0;i<size;i++)
	{
		numbers[i].value = num[i];
		numbers[i].size = 0;
		maxIndexes[i] = i;
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
			printf("CMAX:%d ",cMaxIndex);

		}
		count = index;
		printf("\nCOUNT:%d\n",count);
	}	
}

int getSecondMax()
{
	int secondMax=0, i;

	for (i=0;i<numbers[maxIndexes[0]].size;i++)
	{
		if(numbers[maxIndexes[0]].preMax[i] > secondMax) secondMax = numbers[maxIndexes[0]].preMax[i];
	}
	return secondMax;
}


int main () 
{
	initialize(size_total);
	calculateTwoMaxUsingTournamentMethod(size_total);

	printf("Maximum = %d\n",numbers[maxIndexes[0]]);
	printf("Second Max = %d\n", getSecondMax());
	
	return 0;
}