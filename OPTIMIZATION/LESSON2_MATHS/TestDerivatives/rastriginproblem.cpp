#include "rastriginproblem.h"
# include <math.h>
# include <stdio.h>

RastriginProblem::RastriginProblem()
{
    dimension = 2;
    left.resize(dimension);
    right.resize(dimension);
    for(int i=0;i<dimension;i++)
    {
        left[i]= -1.0;
        right[i]= 1.0;
    }
    functionCalls = 0;
}

Data    RastriginProblem::getRandomSample()
{
    Data x;
    x.resize(dimension);
    for(int i=0;i<dimension;i++)
    {
        x[i]=left[i]+rand()*1.0/RAND_MAX*(right[i]-left[i]);
    }
    return x;
}

double  RastriginProblem::funmin(Data &x)
{
    functionCalls++;
    return x[0]*x[0]+x[1]*x[1]-cos(18.0*x[0])-cos(18.0*x[1]);
}

Data    RastriginProblem::gradient(Data &x)
{
    Data g;
    g.resize(dimension);
    g[0]=2.0*x[0]+18.0*sin(18.0*x[0]);
    g[1]=2.0*x[1]+18.0*sin(18.0*x[1]);
    return g;
}

Data    RastriginProblem::finiteGradient1(Data &x)
{
    const double h=1e-6;
    Data x1,g;
    x1.resize(dimension);
    g.resize(dimension);
    double fx = funmin(x);
    x1=x;

    for(int i=0;i<dimension;i++)
    {
        x1[i]=x[i]+h;
        g[i]=(funmin(x1)-fx)/h;
        x1[i]=x1[i]-h;
    }
    return g;
}

static double dmax(double a,double b)
{
    return a>b?a:b;
}

Data    RastriginProblem::finiteGradient2(Data &x)
{
    Data x1,x2,g;
    x1.resize(x.size());
    x2.resize(x.size());
    g.resize(x.size());
    x1=x;
    x2=x;
    for(int i=0;i<dimension;i++)
    {
       double h = pow(1e-18,1.0/3.0)*dmax(1.0,fabs(x[i]));
       x1[i]=x[i]+h;
       x2[i]=x[i]-h;
       g[i]=(funmin(x1)-funmin(x2))/(2.0*h);
       x1[i]=x1[i]-h;
       x2[i]=x2[i]+h;
    }
    return g;
}

double  RastriginProblem::grms(Data &g)
{
    double s = 0.0;
    for(int i=0;i<dimension;i++)
        s+=g[i]*g[i];
    return s;
}


int     RastriginProblem::getDimension()   const
{
    return dimension;
}

Data    RastriginProblem::getLeftMargin()  const
{
    return left;
}

Data    RastriginProblem::getRightMargin() const
{
    return right;
}

int     RastriginProblem::getFunctionCalls() const
{
    return functionCalls;
}

void    RastriginProblem::resetFunctionCalls()
{
    functionCalls = 0;
}

RastriginProblem::~RastriginProblem()
{
    //nothing here
}
