#include "gradientwithls.h"




GradientWithLS::GradientWithLS(Problem *p)
    :GradientDescent(p)
{

}

double  GradientWithLS::fl(double h)
{
    Data trialx = xpoint;
    unsigned int i;
    Data g = myProblem->gradient(xpoint);
    for(i=0;i<xpoint.size();i++)
    {
        trialx[i]=trialx[i]-h * g[i];
    }
    return myProblem->funmin(trialx);
}

void GradientWithLS::goldenSearch(double &a,double &b)
{
    double phi = (sqrt(5.0)-1.0)/2.0;
    int iteration = 1;
    while(true)
    {
        double x1 = a+(1-phi)*(b-a);
        double x2 = a+phi * (b-a);
        double diff =fabs(x1-x2);
        if(diff<1e-6) break;

        if(fl(x1)<fl(x2))
        {
            b = x2;
        }
        else
        {
            a=x1;
        }
        iteration++;

    }
}

void    GradientWithLS::updateRate()
{
    double lambda = rate;
    double a = lambda * 0.5;
    double b = lambda * 1.5;
    goldenSearch(a,b);
    rate = a;
}
