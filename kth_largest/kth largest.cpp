#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#define SIZE 100005

void min_heapify(int *heap, int heap_size, int i)
{
	int left = 2 * i + 1, right = 2 * i + 2, smallest = i;

	if (left  < heap_size && heap[left]  < heap[smallest]) smallest = left;
	if (right < heap_size && heap[right] < heap[smallest]) smallest = right;
	if (smallest != i)
	{
		heap[i] ^= heap[smallest] ^= heap[i] ^= heap[smallest];
		min_heapify(heap, heap_size, smallest);
	}
}

void build_min_heap(int *heap, int heap_size)
{
	for(int i = heap_size / 2 - 1; i >= 0; i--)
		min_heapify(heap, heap_size, i);
}

int kthLargest(int a[], int size, int k) 
{ 
	int minHeap[SIZE]; 
	int i; 
	for(i=0;i<k;i++) 
		minHeap[i] = a[i]; 
	build_min_heap(minHeap,k); 
	
	for(i=k;i<size;i++) 
		if(a[i]>minHeap[0]) 
		{ 
			minHeap[0]=a[i]; 
			min_heapify(minHeap,k,0); 
		} 
	return minHeap[0]; 
}

int n;
int ara[SIZE];

int main() 
{

	int i;	
	n = 100000;
	
	freopen("out.txt","w",stdout);
	//input array
	for (i=1;i<=n;i++)ara[i] = i;
	
	clock_t start, end;
	double runTime=0.0;
	int k = 100,value;

	
	start = clock();
	value = kthLargest(ara,n,k);
	end = clock();
	runTime = (end - start) / (double) (CLOCKS_PER_SEC) ;
	printf("%dth largest value is:%d\n",k, value);
	printf("Total RunTime for %dth largest from %d numbers is: %lfms\n",k, n,runTime);
	
	return 0; 
}


