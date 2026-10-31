#include "purerandomsearch.h"



PureRandomSearch::PureRandomSearch(Problem *p)
{
    myProblem = p ;
    nsamples = 100;
    maxiters = 100;
    besty = 1e+100;
}

void    PureRandomSearch::setMaxiters(int m)
{
    if(m>0) maxiters=m;
}


int     PureRandomSearch::getMaxiters() const
{
    return maxiters;
}

void PureRandomSearch::setNsamples(int n)
{
    if(n>0) nsamples = n;
}

int  PureRandomSearch::getNsamples() const
{
    return nsamples;
}

void    PureRandomSearch::Step()
{
    for(int i=1;i<=nsamples;i++)
    {
        Data x = myProblem->getSample();
        double y = myProblem->statFunmin(x);
        if(y<besty)
        {
            besty = y;
            bestx = x;
        }
    }
}

bool    PureRandomSearch::Terminated()
{
  ++iter;
  printf("ITER=%4d BEST VALUE=%20.10lg GRMS=%20.10lg\n",
         iter,besty,myProblem->grms(bestx));
  return iter>=maxiters;
}

void    PureRandomSearch::Solve()
{
    iter = 0;
    do
    {
        Step();
    }while(!Terminated());
}

Data    PureRandomSearch::getBestx()
{
    return bestx;
}

double  PureRandomSearch::getBesty()
{
    return besty;
}

PureRandomSearch::~PureRandomSearch()
{
    //nothing here
}
