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
	return final;
}

float dist(int *l, int n)
{
	int l1[3],l2[3],l3[3],i,l1_size=0,l2_size=0,l3_size=0;
	int rem;
	float f=0.0;
	for(i=0; i<n; i++)
	{
		rem=i%3;
		switch(rem)
		{
			case 0:
				l1[l1_size]=l[i];
				l1_size++;
				break;
			case 1:
				l2[l2_size]=l[i];
				l2_size++;
				break;
			case 2:
				l3[l3_size]=l[i];
				l3_size++;
				break;
		}
	}
	f=f+mrt(l1,l1_size);
	f=f+mrt(l2,l2_size);
	f=f+mrt(l3,l3_size);
	return (f/n);	
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
	
	MRT=dist(l,n);
	
	printf("Final MRT : %f\n",MRT);	
}
