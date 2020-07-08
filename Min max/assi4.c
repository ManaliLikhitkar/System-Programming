#include<stdio.h>
#include<math.h>
#include<stdlib.h>


void min_max(int *p, int low, int high, int ans[2])
{
	int n;
	n=high-low+1;
	if(n==1)
	{
		ans[0]=p[low];
		ans[1]=p[high];
	}
	else if(n==2)
	{
		if(p[low]<p[high])
		{
			ans[0]=p[low];
			ans[1]=p[high];
		}
		else
		{
			ans[0]=p[high];
			ans[1]=p[low];
		}
	}
	else
	{
		int mid;
		int l[2],r[2];		
		mid=(low+high)/2;
				
		min_max(p,low,mid,l);
		min_max(p,mid+1,high,r);
		
		if(l[1]>r[1])
			ans[1]=l[1];
		else
			ans[1]=r[1];
		if(l[0]<r[0])
			ans[0]=l[0];
		else
			ans[0]=r[0];
	}
}

int main()
{
	int i,n;
	int ans[2];
	printf("\nEnter the total number of elements : ");
	scanf("%d",&n);
	
	int *p;
	p=(int*)malloc(n * sizeof(int));
	
	printf("Enter the elements :\n");
	for(i=0; i<n; i++)
	{
		if (p==NULL) 
		{ 
			printf("Memory not allocated.\n"); 
			break;
    		} 
    		scanf("%d",&p[i]);
	}
	
	printf("\n\nThe elements are :\n");
	for(i=0; i<n; i++)
	{
		printf("%d\n",p[i]);
	}
		
	min_max(p,0,n-1,ans);
	
	printf("\n\nAnswer :\nMinimum : %d\nMaximum : %d\n",ans[0],ans[1]);
}
