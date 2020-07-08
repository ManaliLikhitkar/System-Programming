#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int x[8],total;

void print(int n)
{
	printf("\n\n\n");
	int i,j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<n; j++)
		{
			if(x[i]==j)
				printf(" Q%d ",i+1);
			else
				printf(" -- ");
		}
		printf("\n");
	}
}

int place(int k,int i)
{
	int j;
	for(j=0; j<k; j++)
	{
		if(x[j]==i || abs(x[j]-i)==abs(j-k))
			return 0;			
	}
	return 1;
}

void Nqueens(int k, int n)
{
	int i;
	for(i=0;i<n; i++)
	{
		if(place(k,i)==1)
		{
			x[k]=i;
			if(k==n-1)
				print(n);
			else
				Nqueens(k+1,n);
		}
	}
}

int main()
{
	int n;
	printf("Enter the size of chessboard : ");
	scanf("%d",&n);
	
	Nqueens(0,n);
}
