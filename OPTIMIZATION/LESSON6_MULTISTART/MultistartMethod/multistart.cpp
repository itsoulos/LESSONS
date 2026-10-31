#include "multistart.h"


Multistart::Multistart(Problem *p)
{
    myProblem = p ;
    nsamples = 100;
    maxiters = 100;
    besty = 1e+100;
}

void    Multistart::setMaxiters(int m)
{
    if(m>0) maxiters=m;
}


int     Multistart::getMaxiters() const
{
    return maxiters;
}

void Multistart::setNsamples(int n)
{
    if(n>0) nsamples = n;
}

int  Multistart::getNsamples() const
{
    return nsamples;
}

void    Multistart::Step()
{
    for(int i=1;i<=nsamples;i++)
    {
        Data x = myProblem->getSample();
        double y = myProblem->statFunmin(x);
        GradientWithLS gd(myProblem);
        gd.setPoint(x,y);
        gd.Solve();
        x = gd.getBestx();
        y = gd.getBesty();
        if(y<besty)
        {
            besty = y;
            bestx = x;
        }
    }
}

bool    Multistart::Terminated()
{
  ++iter;
  printf("ITER=%4d BEST VALUE=%20.10lg GRMS=%20.10lg\n",
         iter,besty,myProblem->grms(bestx));
  return iter>=maxiters;
}

void    Multistart::Solve()
{
    iter = 0;
    do
    {
        Step();
    }while(!Terminated());
}

Data    Multistart::getBestx()
{
    return bestx;
}

double  Multistart::getBesty()
{
    return besty;
}

Multistart::~Multistart()
{
    //nothing here
}
