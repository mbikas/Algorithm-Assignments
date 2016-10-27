
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define SIZE 1000

typedef struct{
	
	int value;
	int pre_position;
}array;

array ara[SIZE];
int size;


int comp(const void* A, const void* B)
{
	array *a=(array*)A;
	array *b=(array*)B;	
	
	if(a->value < b->value) return(-1);
	if(a->value > b->value) return(1);	
    return (0);

}
void main()
{
	int value,i;
	freopen("in.txt","r",stdin);

	//35, 67, 12, 7, 42

	size = 0;
	while( scanf("%d",&value) !=EOF)
	{
		ara[size].value = value;
		ara[size].pre_position = size+1;
		size++;
	}
	
	printf("Before Sorting\n------------------\n");
	for(i=0;i<size;i++)
	printf("%d %d\n",ara[i].value,ara[i].pre_position);
	printf("------------------\nAfter Sorting\n");

	
	qsort(ara,size,sizeof(array),comp);

	for(i=0;i<size;i++)
	printf("%d %d %d \n",ara[i].value,ara[i].pre_position, i+1);
	
	int ans[SIZE];
	memset(ans, 0,sizeof(ans));
	
	for(i=0;i<size;i++)
		ans[ara[i].pre_position] = i+1;
	for(i=1;i<=size;i++)
		printf("%d",ans[i]);
}

