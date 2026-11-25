# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <vector>
using namespace std;

int 	select(vector<double> x)
{
	double totalf = 0.0;
	for(int i=0;i<x.size();i++)
		totalf+=x[i];
	double value = (rand()*1.0/RAND_MAX)*totalf;
	double sum = 0.0;
	for(int i=0;i<x.size();i++)
	{
		sum+=x[i];
		if(sum>=value) return i;
	}
	return x.size()-1;
}

void sortf(vector<double> &x)
{
	for(int i=0;i<x.size();i++)
	{
		for(int j=0;j<x.size()-1;j++)
		{
			if(x[j+1]<x[j])
			{
				double t = x[j];
				x[j]=x[j+1];
				x[j+1]=t;
			}
		}
	}
}

int main()
{
	vector<double> x;
	vector<int>    count;
	int  elements;
	int M,k,i;
	double left,right;
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
		x[i]=left+(right-left)*rand()/RAND_MAX;
		printf("x[%d]=%lf\n",i,x[i]);
		count[i]=0;
	}
	sortf(x);
	do
	{
		printf("HOW MANY ATOMS WILL BE SELECTED ?");
		scanf("%d",&M);
	}while(M<=0);	
	for(i=0;i<M;i++)
	{
		k=select(x);
		printf("SELECTED ELEMENT %d  WITH FITNESS %lf  \n",k,x[k]);
		count[k]++;
	}
	for(i=0;i<x.size();i++)
	{
		printf("ATOM %d SELECT %.2lf%%\n",i,count[i]*100.0/M);
	}
	return 0;
}
