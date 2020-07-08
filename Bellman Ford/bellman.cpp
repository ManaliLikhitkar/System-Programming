#include<iostream>
using namespace std;


typedef struct
{
	int u,v,cost;
}edeg;

int main()
{
	int distance[20],parent[20];
	int n,i,j=0,flag=0,u,v,noe;
	int cnt=1,startvertex;
	int mat[20][20];
	edeg e[20];
	
	cout<<"Enter No of Nodes :: ";
	cin>>n;
	cout<<"\nEnter No of Edges :: ";
	cin>>noe;
	cout<<endl;
	for(int i=0;i<noe;i++)
	{
		cout<<"Enter Edge and Its Cost :: \n";
		cout<<"Vertex V1 :: ";
		cin>>e[i].u;
		cout<<"Vertex V2 :: ";
		cin>>e[i].v;
		cout<<"Cost Is :: ";
		cin>>e[i].cost;
		cout<<endl;
	}
	cout<<endl<<"Edges Are ::\n";
	for(int i=0;i<noe;i++)
	{
		cout<<e[i].u<<"-"<<e[i].v<<" :: "<<e[i].cost;
		cout<<endl;
	}
	cout<<endl;
	for(i=0;i<n;i++)
	{
		distance[i]=9999;
		parent[i]=-1;
	}
		
	cout<<"Enter Startvertex :: ";
	cin>>startvertex;
	distance[startvertex]=0;
	parent[startvertex]=startvertex;
	
	for (u=0;u<n;u++)
	{
		flag=0;
		cout<<"\nNo of Hops "<<j+1<<endl<<endl;
		for(v=0;v<noe;v++)
		{
			if(distance[e[v].v] > distance[e[v].u]+e[v].cost)
			{
				distance[e[v].v]=distance[e[v].u]+e[v].cost;
				parent[e[v].v]=e[v].u;
				flag=1;
			}
		}

		for(int c=0;c<n;c++)
		{
			cout<<"d["<<c<<"] :: "<<distance[c]<<"\t";
		}
		cout<<endl;
		for(int c=0;c<n;c++)
		{
			cout<<"p["<<c<<"] :: "<<parent[c]<<"\t";
		}
		cout<<endl<<endl;
		
		if(flag==0)
			break;
					
		j++;
	}
	
	for(v=0;v<noe;v++)
	{
		if(distance[e[v].v] > distance[e[v].u]+e[v].cost)
		{
			cout<<"\nNegative Cycle Is Detected\n";
		}
	}

	return 0;
}
