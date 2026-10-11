# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <vector>
using namespace std;
typedef vector<double> Data;

double randomNumber()
{
    const double width = 0.04;
    double r = rand()*1.0/RAND_MAX;
    if(r<0) r=-r;
    return width*(2*r-1);
}

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return sin(x)+randomNumber();
}


double distance(Data &x,Data &y)
{
    double s = 0.0;
    for(unsigned int i=0;i<x.size();i++)
        s+=(x[i]-y[i])*(x[i]-y[i]);
    return sqrt(s/x.size());
}


int main()
{
    int npoints=1000;
    double a= -4;
    double b=  4;
    double dx = (b-a)/npoints;
    Data f1_vector;
    Data f2_vector;
    for(double x=a;x<=b;x+=dx)
    {
        double y1 = f1(x);
        double y2 = f2(x);
        printf("%lf %lf %lf\n",x,y1,y2);
        f1_vector.push_back(y1);
        f2_vector.push_back(y2);
    }
    double dist = distance(f1_vector,f2_vector);
    printf("Function Distance = %20.10lg\n",dist);
    //sxedon panta einai peripou to miso tou width!!
    return 0;
}
