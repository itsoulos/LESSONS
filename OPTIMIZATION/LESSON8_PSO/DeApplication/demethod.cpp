#include "demethod.h"

DeMethod::DeMethod(Problem *p)
{
    myProblem = p;
    NP = 10 * p->getDimension();
    F=0.8;
    CR=0.9;
    maxiters = 1000;
}

void    DeMethod::setNP(int n)
{
    if(n>0) NP = n;
}

int     DeMethod::getNP() const
{
    return NP;
}

void    DeMethod::setF(double f)
{
    if(f>0) F = f;
}

double  DeMethod::getF() const
{
    return F;
}

void    DeMethod::setCR(double c)
{
    if(c>0 && c<1) CR = c;
}

double  DeMethod::getCR() const
{
    return CR;
}

bool DeMethod::Terminated()
{
    printf("DE. ITER=%4d BESTVALUE=%20.10lg\n",iter,besty);
    double miny,maxy;
    agent.getBestWorstValues(miny,maxy);
    return iter>=maxiters || fabs(maxy-miny)<1e-4;
}

void DeMethod::Step()
{
   ++iter;
   for(int i=0;i<NP;i++)
   {
       Data x;
       double y;
       agent.getPoint(i,x,y);
       int randomA,randomB,randomC;
       do
       {
           randomA = rand() % NP;
           randomB = rand() % NP;
           randomC = rand() % NP;
       }while(randomA == randomB || randomB == randomC || randomA == randomC);
       Data xa,xb,xc;
       double ya,yb,yc;
       agent.getPoint(randomA,xa,ya);
       agent.getPoint(randomB,xb,yb);
       agent.getPoint(randomC,xc,yc);
       int R = rand() % myProblem->getDimension();
       Data trialx = x;
       for(int j=0;j<myProblem->getDimension();j++)
       {
           double rj = rand() *1.0/RAND_MAX;
           if(rj<CR || j==R)
           {
                trialx[j]=xa[j]+F*(xb[j]-xc[j]);
           }
           else trialx[j]=x[j];
       }
        if(!myProblem->isPointIn(trialx)) trialx = x;
        double ft = myProblem->statFunmin(trialx);
        if(ft<y)
        {
            agent.replacePoint(i,trialx,ft);
            if(ft<besty)
            {
                besty = ft;
                bestx = trialx;
            }
        }
   }
}

void DeMethod::Solve()
{
    iter = 0;

    //sampling
    for(int i=0;i<NP;i++)
    {
        Data x= myProblem->getSample();
        double y = myProblem->statFunmin(x);
        if(i==0 || y<besty)
        {
            besty = y;
            bestx = x;
        }
        agent.addPoint(x,y);
    }
    do
    {
        Step();

    }while(!Terminated());
    //apply a local search to the best point
    GradientWithLS gd(myProblem);
    gd.setLineSearch("armijo");
    gd.setPoint(bestx,besty);
    gd.Solve();
    bestx = gd.getBestx();
    besty = gd.getBesty();
}

void    DeMethod::setMaxiters(int i)
{
    if(i>0) maxiters =i;
}

int     DeMethod::getMaxiters() const
{
    return maxiters;
}

Data    DeMethod::getBestx()
{
    return bestx;
}

double  DeMethod::getBesty()
{
    return besty;
}

DeMethod::~DeMethod()
{

}
