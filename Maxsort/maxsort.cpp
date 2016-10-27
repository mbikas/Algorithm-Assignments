#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE 100
#define STRING_SIZE 20

void swap(char *str1, char *str2)
{
  char *temp = (char *)malloc((strlen(str1) + 1) * sizeof(char));
  strcpy(temp, str1);
  strcpy(str1, str2);
  strcpy(str2, temp);
  free(temp);
}

int main()
{
	
	char A[ARRAY_SIZE][STRING_SIZE];
	char max[STRING_SIZE];
	int total = 0,i,j, maxIndex, size;

	//getting input from a file
	freopen("input.txt","r",stdin);
	while(scanf(" %s",A[total])==1)
	{
		total++;
	}
	/*
	//getting input from console
	scanf("%d",&total);
	for(i=0;i<total;i++)scanf(" %s",A[i]);
	*/
	
	for (i=0;i<total;i++)
		printf("%s\n",A[i]);
	for (i=0;i<total;i++)
	{
		maxIndex = 0;
		strcpy(max, A[0]);
		size = total-i-1;
		for (j=1;j<size;j++)
		{
			if (strcmp(A[j], max) >0)
			{
				strcpy(max, A[j]);
				maxIndex = j;
			}
		}	
		if (strcmp(max, A[size]) >0)
			swap2(A[maxIndex],A[size]); 
	}
	for (i=0;i<total;i++)
		printf("%s\n",A[i]);		
	return 0;
}
