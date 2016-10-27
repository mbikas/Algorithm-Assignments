#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<time.h>

#define SIZE 100005


int n, ara[SIZE];
void build_max_heap(int *heap, int heap_size);
void max_heap_sort(int *ara, int n);

int main(void)
{
	int i;	
	n = 100000;

	//input array
	for (i=1;i<=n;i++)ara[i] = i;
		
	clock_t start, end;
	double runTime=0.0;

	/*
	freopen("in.txt", "rt", stdin);
	while(scanf(" %d", &n) == 1 && n)
	{
		for(i = 0; i < n; i++)
			scanf(" %d", &ara[i]);
	}
	*/

	start = clock();
	build_max_heap(ara, n);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("Total RunTime for Bottom-Up Implementation of %d values is: %lfms\n",n,runTime);
	
	return(0);
}

/*******************************************************Heap************************************************************/
/*
	For 0-based heap:									For 1-based heap:
		1. parent: (i - 1) / 2;							1. parent: i / 2;
		2. left-child:  2 * i + 1;						2. left-child:  2 * i;
		3. right-child: 2 * i + 2;						3. right-child: 2 * i + 1;
		4. last-parent: n / 2;							4. last-parent: n / 2 - 1;
*/

void max_heapify(int *heap, int heap_size, int i)
{
	int left = 2 * i + 1, right = 2 * i + 2, largest = i;

	if (left  < heap_size && heap[left]  > heap[largest]) largest = left;
	if (right < heap_size && heap[right] > heap[largest]) largest = right;
	if (largest != i)
	{
		heap[i] ^= heap[largest] ^= heap[i] ^= heap[largest];
		max_heapify(heap, heap_size, largest);
	}
}

void build_max_heap(int *heap, int heap_size)
{
	for(int i = heap_size / 2 - 1; i >= 0; i--)
		max_heapify(heap, heap_size, i);
}

//Heap_sort for max_heap.
void max_heap_sort(int *ara, int n)
{
	build_max_heap(ara, n);
	for(int i = n - 1; i >= 1; i--)
	{
		ara[i] ^= ara[0] ^= ara[i] ^= ara[0];
		max_heapify(ara, --n, 0);
	}
}

