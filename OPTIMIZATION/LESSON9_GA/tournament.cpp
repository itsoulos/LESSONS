# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <vector>
using namespace std;

int 	select(vector<double> x,int tsize)
{
	int imax=-1;
	double maxx=-1e+100;
	for(int i=0;i<tsize;i++)
	{
		int r=rand() % x.size();
		if(x[r]>maxx)
		{
			imax=r;
			maxx=x[r];
		}
	}
	return imax;
}

int main()
{
	vector<double> x;
	vector<int>    count;
	int  elements;
	int M,k,i;
	double left,right;
	int tournament_size;
	srand48(0);
	srand(0);

	do
	{
		printf("HOW MANY ELEMENTS FOR THE DOUBLE VECTOR ? ");
		scanf("%d",&elements);
	}while(elements<=0);
	x.resize(elements);
	count.resize(elements);
	do
	{
		printf("ENTER LEFT BOUND FOR X ");
		scanf("%lf",&left);
	}while(left<0);	
	do
	{
		printf("ENTER RIGHT BOUND FOR X ");
		scanf("%lf",&right);
	}while(right<left || right<0);
	for(i=0;i<x.size();i++)
	{
		x[i]=left+(right-left)*drand48();
		printf("x[%d]=%lf\n",i,x[i]);
		count[i]=0;
	}
	do
	{
		printf("ENTER TOURNAMENT SIZE ");
		scanf("%d",&tournament_size);
	}while(tournament_size<2);
	do
	{
		printf("HOW MANY ATOMS WILL BE SELECTED ?");
		scanf("%d",&M);
	}while(M<=0);	
	for(i=0;i<M;i++)
	{
		k=select(x,tournament_size);
		printf("SELECTED ELEMENT %d  WITH FITNESS %lf  \n",k,x[k]);
		count[k]++;
	}
	for(i=0;i<x.size();i++)
	{
		printf("ATOM %d SELECT %.2lf%%\n",i,count[i]*100.0/M);
	}
	return 0;
}
