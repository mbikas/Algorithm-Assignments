#include<stdio.h>
#include<string.h>

#define ROW 100
#define COL 100

int nRows, nCols;
char graph[ROW][COL]; //used this to store the graph nodes
bool visited[ROW][COL]; // used this 2D array to track already visited nodes during recursion
bool whiteFound;
bool blackFound;

void processInputFromFile(bool isInputFromFile);
void addToCandidateListIfEmplyAndValid(int c_row, int c_col, int c[][2], int *ncandidate);
void construct_candidate(int row,int col,int c[][2],int *ncandidate);
void isBlackOrWhiteReachable(int row, int col);

//used backtracking approach with memoization technique
int main()
{
	int inputMethod;
	
	printf("Press 1 to take input graph from console\n");
	printf("Press 2 to take input from file\n");
	scanf("%d",&inputMethod);
	
	if(inputMethod == 1)
		processInputFromFile(false);
	else if(inputMethod == 2)
		processInputFromFile(true);		
	
	return 0;
}

void processInputFromFile(bool isInputFromFile)
{
	int row, col, black, white, line, i;
	
	if(isInputFromFile)
	{
		freopen("input.txt","r",stdin);
		//freopen("output.out","w",stdout);
	}
	
	line = 0;
	nRows = nCols = 0;
	if (!isInputFromFile)	printf("Enter Number of rows and Cols\n");
	while ( scanf("%d %d",&nRows, &nCols) == 2)
	{
		if (!isInputFromFile)
			printf("Now Enter Values for %d rows each with %d values.\nExample Format: BEBEEEEEE  [assuming no of column is 9]\n",nRows,nCols);
		for (i = 0; i< nRows; i++)
			scanf(" %[^\n]",graph[i]);
		
		black = white = 0;
		memset(visited, false, sizeof(visited[0]) );
		for (row=0;	row<nRows;	row++)
		{
			for(col=0;	col<nCols;	col++)
			{
				if(graph[row][col]	==	'E')
				{
					whiteFound = false;
					blackFound = false;
					isBlackOrWhiteReachable(row, col);
					if(whiteFound == true && blackFound == false)white++;
					if(blackFound == true && whiteFound == false)black++;

				}
			}
		}			
		printf("Score for Black: %d\n",black);
		printf("Score for White: %d\n",white);
	}
}


void addToCandidateListIfEmplyAndValid(int c_row, int c_col, int c[][2], int *ncandidate)
{
	if( (c_row >= 0 && c_row <= nRows) && (c_col >= 0 && c_col <= nCols))
	{
		if(graph[c_row][c_col] == 'W') whiteFound = true;
		if(graph[c_row][c_col] == 'B') blackFound = true;		
		if(visited[c_row][c_col] == false && graph[c_row][c_col] == 'E')
		{
			c[(*ncandidate)][0]=c_row;	
			c[(*ncandidate)][1]=c_col;
			(*ncandidate)++;
		}
	}
}

void construct_candidate(int row,int col,int c[][2],int *ncandidate)
{
	(*ncandidate) = 0;	

	//up
	addToCandidateListIfEmplyAndValid(row, col-1, c , ncandidate);	

	//down
	addToCandidateListIfEmplyAndValid(row, col+1, c , ncandidate);
	
	//left
	addToCandidateListIfEmplyAndValid(row-1, col, c , ncandidate);
	
	//right
	addToCandidateListIfEmplyAndValid(row+1, col, c , ncandidate);	
}



void isBlackOrWhiteReachable(int row, int col)
{
	int i,candidates[100][2],ncandidate=0;
	
	construct_candidate(row, col,candidates,&ncandidate);	
	for(i=0;i<ncandidate;i++)
	{	
		visited[candidates[i][0]][candidates[i][1]]=true;		
		isBlackOrWhiteReachable(candidates[i][0], candidates[i][1]);
		visited[candidates[i][0]][candidates[i][1]]=false;
		if(whiteFound && blackFound)return;
			
	}
}

