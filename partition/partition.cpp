#include <stdio.h>

#define MAX_SUM			1000	//can be maximum sum/2+1
#define MAX_NUM_COUNT	100		//can be maximum n+1
bool partition[MAX_SUM][MAX_NUM_COUNT];	//2D table used for DP
int sum = 0;


int input[] = {3,3,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,7,7,7,7,8,8,9,9,9,10,10,10,10,11,11,11,11,12,13,15,15,15,17,20,21,21,27,31,34,55};

int noOfInput;
bool subset[MAX_NUM_COUNT]; //to indicate the subsets

//true if input[] can be paritioned into two subset
//false otherwise
//dp approach:
//creating 2D array partition[][] of size (sum/2)*(n+1)
//Now constructing the solution in bottom up manner such that:
//partition[i][j] = true if a subset of {arr[0], arr[1], ..arr[j-1]} has sum equal to i, otherwise false
bool isPartitionPossible(int input[], int n)
{
    sum = 0;
    int i, j;
   
   	//if the total sum can not be divide/2 then return false
    for (i = 0; i < n; i++)	sum += input[i];
    if (sum%2 != 0) 	return false;
   
   
    // initializing top row and left col
    for (i = 0; i <= n; i++)		partition[0][i] = true;
    for (i = 1; i <= sum/2; i++)	partition[i][0] = false;    
      
     //Filling out the partition table in botton up manner
     for (i = 1; i <= sum/2; i++) 
     {
       for (j = 1; j <= n; j++) 
       {
         	partition[i][j] = partition[i][j-1];
         	if (i >= input[j-1])
           		partition[i][j] = partition[i][j] || partition[i - input[j-1]][j-1];
       }       
     }         
     return partition[sum/2][n];
}    

void printPath(int sum)
{
	if(sum == 0)return;
	int index = 0;
	for(int j=1; j<=noOfInput; j++)
	{
		if(partition[sum][j] == true)
		{
			index = j-1;
			break;
		}
	}	
	printPath((sum - input[index]));
	subset[j-1] = true;
	//printf("%d ",j-1);
}

//print the subsets that partitions numbers with equals sum
//flag = true means first subset
//flag = fasle means 2nd subset
void printValues(bool flag)
{
	int set = 2;
	if(flag) set = 1;
	printf("Subset%d:\n--------\n",set);
	int count=0, s = 0;
	for(int i=0;i<noOfInput;i++)
	{
		if(subset[i] == flag){
				printf("%d ",input[i]);
				count++;
				s += input[i];
		}
	}
	printf("\nNo in Subset%d = %d\nSum of Subset%d = %d\n----------\n", set, count, set, s);
}

void printfInput(int input[], int noOfInput)
{
	printf("Input\n--------\n");
	int count=0, sum = 0;
	for(int i=0;i<noOfInput;i++)
	{
		printf("%d ",input[i]);
		count++;
		sum += input[i];
	}
	printf("\nTotal No of values= %d\nSum of the Values= %d\n----------\n\n", count, sum);
}
 
// Driver program to test above funtion
int main()
{
	freopen("output.txt", "w", stdout);

  	noOfInput = sizeof(input)/sizeof(input[0]);
	
	///5(a)
	printfInput(input, noOfInput);
	printf("\nOutput\n--------\n");
	if (isPartitionPossible(input, noOfInput) == true)
		printf("Possible to partition\n");
	else
		printf("Can to be partitioned\n");

	
	//5(b)
	//intializing subset with 0
	for(int i=0;i<noOfInput;i++)subset[i]= false;
	//inside the recusion the first subset will be indicated with true
	printPath(sum/2);
	//printing both subset

	printValues(true);
	printValues(false);
	
	return 0;
}

//References: 
//http://en.wikipedia.org/wiki/Partition_problem
