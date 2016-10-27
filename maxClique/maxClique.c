#include<stdio.h>
#include<stdlib.h>

typedef struct{
	char name[50];
	double birthYear;
	double deathYear;
}President;
President presidents[100];

int comp(void const *A, void const *B)
{
	President *a = (President*)A;
	President *b = (President*)B;
	return a->birthYear - b->birthYear;
}
int n=0;

int getMaximumClique()
{
	int i, j,clique = 0;
	int maxClique = 1;
	
	for(i = 0; i < n-1; i++)
	{
		clique = 1;
		for (j=i;j>=0;j--)
			if(presidents[j].deathYear >= presidents[i+1].birthYear)clique++;	
		if(clique > maxClique) maxClique = clique;
	}
	return maxClique;
}


//complexity of the algorithm: 
//sorting the numbers using quick sort: nlogn
//finding the maximum clique: n^2
//Complexity: O(n^2)

int main()
{
	int maxClique;

	/*
		taking input from file
		format: name birthYear deathYear	
	*/
	//freopen("sample_input1.txt","r",stdin);
	//freopen("sample_input2.txt","r",stdin);
	freopen("presidents.txt","r",stdin);
	n = 0;
	while(scanf(" %s %lf %lf",presidents[n].name, &presidents[n].birthYear, &presidents[n].deathYear)==3)
	{
		//printf("%s %lf %lf\n",presidents[n].name, presidents[n].birthYear, presidents[n].deathYear);
		n++;
	}
	
	//soring the president information based on the birthYear
	qsort(presidents,n,sizeof(President),comp);
	
	maxClique = getMaximumClique();
	printf("Maximum number of people alive at one time in US history, who are, have been, or will one day be a US president(Maximum Clique): %d\n",maxClique);
	
	return 0;
}
