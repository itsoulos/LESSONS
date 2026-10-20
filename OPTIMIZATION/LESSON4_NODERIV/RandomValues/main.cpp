#include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include <vector>
using namespace std;
typedef vector<double> Data;

double  getMean(Data &x)
{
    double s= 0.0;
    for(int i=0;i<x.size();i++)
    {
        s+=x[i];
    }
    return s/x.size();
}

double  getStd(Data &x)
{
    double mx = getMean(x);
    double s= 0.0;
    for(int i=0;i<x.size();i++)
    {
        s+=(x[i]-mx)*(x[i]-mx);
    }
    return sqrt(s/x.size());
}

void getRandom1(int nums,double &mean,double &std)
{
    Data x;
    for(int i=0;i<nums;i++)
    {
        double r = fabs(rand()*1.0/RAND_MAX);
        x.push_back(r);
    }
    mean = getMean(x);
    std  = getStd(x);
}

void getRandom2(int nums,double a,double b,double &mean,double &std)
{
    Data x;
    for(int i=0;i<nums;i++)
    {
        double r = fabs(rand()*1.0/RAND_MAX);
        r = a+(b-a)*r;
        x.push_back(r);
    }
    mean = getMean(x);
    std  = getStd(x);
}

int selectWithProbability(double prob,int nums)
{
    int icount = 0;
    for(int i=0;i<nums;i++)
    {
        double r = fabs(rand()*1.0/RAND_MAX);
        if(r<=prob)
            icount++;
    }
    return icount;
}

int main()
{
    double mean1,std1,mean2,std2;
    const int nums = 1000000;
    const double a= -2;
    const double b=  2;
    int     times = 0;
    getRandom1(nums,mean1,std1);
    printf("Mean1=%20.10lg Std1=%20.10lg\n",mean1,std1);
    getRandom2(nums,a,b,mean2,std2);
    printf("Mean2=%20.10lg Std2=%20.10lg\n",mean2,std2);
    times = selectWithProbability(0.1,nums);
    printf("Selection rate =%10.2lf%%\n",times * 100.0/nums);
    return 0;
}
