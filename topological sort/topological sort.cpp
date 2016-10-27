#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Size 110

typedef struct
{							//i means node number, pa means which are outdegree
	long pa[Size],n,in,i;	//in means  indegree, n means outdegree
}Graph;

Graph g[Size];
long task[Size],heapsize,pos[Size];

void MinHeapify(Graph g[],long root)
{
	long left,right,ind;
	ind=root;
	left=root<<1;
	right=(root<<1)+1;
	if(left<=heapsize&&g[left].in<g[ind].in)
		ind=left;
	if(right<=heapsize&&g[right].in<g[ind].in)
		ind=right;
	if(ind==root||g[root].in<g[ind].in)
		return;
	pos[g[root].i]=ind;pos[g[ind].i]=root;
	Graph tmp;
	tmp=g[root];g[root]=g[ind];g[ind]=tmp;
	MinHeapify(g,ind);
}

Graph pop(Graph g[])
{
	Graph tmp;
	tmp=g[1];
	g[1]=g[heapsize];
	heapsize--;
	MinHeapify(g,1);
	return tmp;
}

void push(Graph g[],long ind,Graph v)
{
	long child,root,tmp2;
	Graph tmp;
	g[ind]=v;
	child=ind;
	root=child>>1;
	while(root>0&&g[root].in>g[child].in)
	{
		tmp=g[root];
		g[root]=g[child];
		g[child]=tmp;
		tmp2=pos[g[root].i];
		pos[g[root].i]=pos[g[child].i];
		pos[g[child].i]=tmp2;
		child=root;
		root=child>>1;
	}
}

void print(long n)
{
	long i;
	for(i=1;i<=n>>1;i++)
	{
		printf("%ld->%ld,%ld\n",g[i].i,g[i<<1].i,g[(i<<1)+1].i);
	}
	printf("\n");
}

bool TopologicalSort(Graph g[],long n)
{
	long i,j,k;
	Graph tmp;
	for(i=1;i<=n;i++)
	{
		pos[i]=i;
		push(g,i,g[i]);
	}
	heapsize=n;
	//print(n);
	tmp=pop(g);
	j=0;
	n--;
	//print(n);
	task[j++]=tmp.i;
	while(tmp.in==0&&n>0)
	{		
		for(i=0;i<tmp.n;i++)
		{
			k=pos[tmp.pa[i]];
			g[k].in--;
			push(g,k,g[k]);
		}
		n--;
		tmp=pop(g);
		//print(n);
		task[j++]=tmp.i;
	}
	if(n==0)
		return 1;
	else 
		return 0;
}

int main()
{
	//topological_input.txt contains sample graph input from problem a and b
	freopen("topological_input.txt","r",stdin);
	//freopen("topological_output.txt","w",stdout);
	long m,n,i,a,b;
	while(2==scanf("%ld %ld",&n,&m)&&(n||m))
	{
		for(i=1;i<=n;i++)
		{
			g[i].in=g[i].n=0;
			g[i].i=i;
		}
		for(i=0;i<m;i++)
		{
			scanf("%ld %ld",&a,&b);
			g[a].pa[g[a].n++]=b;
			g[b].in++;
		}
		
		if(TopologicalSort(g,n)==0)
			printf("There is cycle\n");
		else
		{
			printf("%ld",task[0]);
			for(i=1;i<n;i++)
				printf(" %ld",task[i]);
			printf("\n");
		}
	}
		
	return 0;
}
