#include "simanmethod.h"


SimanMethod::SimanMethod(Problem *p)
{
    myProblem = p;
    T0=100000.0;
    neps = 100;
    eps = 1e-5;
    xpoint = myProblem->getSample();
    ypoint = myProblem->funmin(xpoint);
}

void    SimanMethod::setPoint(Data &x,double y)
{
    xpoint = x;
    ypoint = y;
}
void    SimanMethod::setT0(double t)
{
    if(t>0) T0 = t;
}

double  SimanMethod::getT0() const
{
    return T0;
}

void    SimanMethod::setNeps(int n)
{
    if(n>0) neps = n;
}
int     SimanMethod::getNeps() const
{
    return neps;
}

void    SimanMethod::setEpsilon(double e)
{
    if(e>0) eps = e;
}

double  SimanMethod::getEpsilon() const
{
    return eps;
}

void    SimanMethod::Solve()
{
    int i;
    int k=1;
    while(true)
    {
        for(i=1;i<=neps;i++)
        {
            Data y = myProblem->getSample();
            double fy = myProblem->funmin(y);
            if(fy<ypoint)
            {
                xpoint = y;
                ypoint = fy;
            }
            else
            {
                double r = fabs((rand()*1.0)/RAND_MAX);
                double ratio = exp(-(fy-ypoint)/T0);
                double xmin = ratio<1?ratio:1;
                if(r<xmin)
                {
                    xpoint = y;
                    ypoint = fy;
                }
            }
        }
        const double alpha = 0.8;
        T0 =T0 * pow(alpha,k);
        k=k+1;
        if(T0<=eps) break;
        printf("Iteration: %4d Temperature: %20.10lg Value: %20.10lg\n",
               k,T0,ypoint);
    }
}

Data    SimanMethod::getX()
{
    return xpoint;
}

SimanMethod::~SimanMethod()
{
    //nothing here
}
