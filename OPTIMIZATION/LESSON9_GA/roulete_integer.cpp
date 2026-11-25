# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <vector>
using namespace std;

int select(vector<double> p,int M)
{
	int start;
	vector<int> v;
	v.resize(M);
	start=1;
	for(int i=0;i<p.size();i++)
	{
		int k=(int)(p[i]*M);
		if(k==0) k=1;
		int last=start+k;
		v.resize(last);
		for(int j=start;j<=last;j++)
			v[j-1]=i;
		start=start+k+1;
	}
	return v[rand() % v.size()];
}


void	makeProb(vector<double> x,vector<double> &p)
{
	p.resize(x.size());
	double sum=0.0;
	for(int i=0;i<x.size();i++) sum+=x[i];
	for(int i=0;i<x.size();i++)
	{
		p[i]=x[i]/sum;
	}
}

int main()
{
	vector<double> x;
	vector<int>    count;
	vector<double>	p;
	int  elements;
	int M,k,i;
	double left,right;
	srand48(0);
	srand(0);
	do
	{
		printf("HOW MANY ELEMENTS FOR THE DOUBLE VECTOR ? ");
		scanf("%d",&elements);
	}while(elements<=0);
	x.resize(elements);
	count.resize(elements);
	p.resize(elements);
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
		count[i]=0;
		printf("x[%d]=%lf\n",i,x[i]);
	}
	makeProb(x,p);
	do
	{
		printf("HOW MANY ATOMS WILL BE SELECTED ?");
		scanf("%d",&M);
	}while(M<=0);	
	for(i=0;i<M;i++)
	{
		k=select(p,x.size() * 4);
		printf("SELECTED ELEMENT %d  WITH FITNESS %lf  \n",k,x[k]);
		count[k]++;
	}
	for(i=0;i<x.size();i++)
	{
		printf("ATOM %d SELECT %.2lf%%\n",i,count[i]*100.0/M);
	}
	return 0;
}
