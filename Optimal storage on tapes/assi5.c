#include<stdio.h>
#include<stdlib.h>

void swap(int *xp, int *yp)  
{  
	int temp = *xp;  
	*xp = *yp;  
	*yp = temp;  
}

void sort(int *l, int n)  
{  
	int i, j;  
	for (i = 0; i < n-1; i++)      
	for (j = 0; j < n-i-1; j++)  
	if (l[j] > l[j+1])  
	    swap(&l[j], &l[j+1]);  
}  

float mrt(int *l,int n)
{
	int i,j,temp;
	float final=0.0;
	for(i=0; i<n; i++)
	{
		temp=0;
		for(j=0; j<=i; j++)
		{
			temp=temp+l[j];	
		}
		final=final+temp;
	}
	return (final/n);
}

int main()
{
	int n,i,*l;
	float MRT;
	
	printf("Enter the number of programs : ");
	scanf("%d",&n);
	
	l=(int*)malloc(n * sizeof(int));
	
	printf("Enter the lengths :\n");
	
	for(i=0; i<n; i++)
	{
		scanf("%d",&l[i]);
	}
	
	sort(l,n);
	
	printf("Sorted lengths :\n");
	for(i=0; i<n; i++)
	{
		printf("%d\n",l[i]);
	}
	
	MRT=mrt(l,n);
	
	printf("Final MRT : %f\n",MRT);
}
