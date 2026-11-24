#include "multistart.h"
# include "gradientwithls.h"

Multistart::Multistart(Problem *p)
{
    myProblem = p ;
    nsamples = 100;
    maxiters = 100;
    besty = 1e+100;
    terminationRule = "iters";
}

void    Multistart::setTerminationRule(string s)
{
    terminationRule = s;
}
string  Multistart::getTerminationRule() const
{
    return terminationRule;
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
    Collection Sample;
    for(int i=1;i<=nsamples;i++)
    {
        Data x = myProblem->getSample();
        double y = myProblem->statFunmin(x);
        GradientWithLS gd(myProblem);
        gd.setMaxIters(2);
        gd.setPoint(x,y);
        x = gd.getBestx();
        y = gd.getBesty();
        Sample.addPoint(x,y);

    }
    Sample.resizeInFraction(0.10);
    for(int i=0;i<Sample.getSize();i++)
    {
        Data x;
        double y;
        Sample.getPoint(i,x,y);
        GradientWithLS gd(myProblem);
        gd.setPoint(x,y);
        gd.Solve();
        x = gd.getBestx();
        y = gd.getBesty();
        minima.addPoint(x,y);
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
    int t = iter * nsamples;
    int w = minima.getSize();
    double wkan =  w*(t-1.0)/(t-w-2.0);
    int v = w-oldminima;
    x1+=v;
    x2+=(v*v);
    double variance = fabs((x1/iter)-(x2/iter)*(x2/iter));
    variance = sqrt(variance);
    if(oldminima!=w)
    {
        stopat = variance/2.0;
        oldminima = w;
    }
  printf("ITER=%4d BEST VALUE=%20.10lg MINIMA NUMBER = %4d KANMINIMA=%.2lf variance=%lf stopat=%lf\n",
         iter,besty,
         w,wkan,variance,stopat);

  if(terminationRule == "iters")
      return iter>=maxiters;
  else
  if(terminationRule == "doublebox")
    return iter>=maxiters || variance<=stopat;
  else
    return iter>=maxiters || (wkan -w)<0.5;
}

void    Multistart::Solve()
{
    iter = 0;
    x1= 0.0;
    x2= 0.0;
    oldminima = 0;
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
