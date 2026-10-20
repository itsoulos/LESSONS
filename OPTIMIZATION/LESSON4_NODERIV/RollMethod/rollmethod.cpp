#include "rollmethod.h"

RollMethod::RollMethod(Problem *p,double stepInitValue)
{
    myProblem = p;
    step.resize(p->getDimension());
    for(int i=0;i<p->getDimension();i++)
        step[i]=stepInitValue;
    xsample.resize(p->getDimension());
    xsample=myProblem->getSample();
    ysample=myProblem->statFunmin(xsample);
}

void    RollMethod::setMaxIters(int n)
{
    maxiters=n;
}

void    RollMethod::setStepArray(const Data &stepValues)
{

    for(int i=0;i<myProblem->getDimension();i++)
        step[i]=stepValues[i];
}



void    RollMethod::Solve()
{
    int iters=0;
    int n=myProblem->getDimension();
    while(iters<=maxiters)
    {
        double fold = ysample;
        for(int i=0;i<n;i++)
        {
            Data xplus = xsample;
            Data xminus = xsample;
            xplus[i]=xsample[i]+step[i];
            xminus[i]=xsample[i]-xminus[i];
            double fplus = myProblem->statFunmin(xplus);
            double fminus = myProblem->statFunmin(xminus);
            if(fplus<ysample)
            {
                xsample = xplus;
                ysample = fplus;
            }
            else
            if(fminus<ysample)
            {
                xsample= xminus;
                ysample = fminus;
            }
            else
            {
                //new step
                step[i]=-0.5 * (fplus-fminus)/(2*fplus*fminus-2.0*ysample);
            }
        }


        printf("Iteration = %d  F=%20.10lg\n",iters,ysample);
        iters=iters+1;
        if(fabs(fold-ysample)<1e-6) break;
    }
}

Data    RollMethod::getBestX() const
{
    return xsample;
}

double  RollMethod::getBestY() const
{
    return ysample;
}

RollMethod::~RollMethod()
{

}
