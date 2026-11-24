#include "gradientwithls.h"


GradientWithLS::GradientWithLS(Problem *p)
    :GradientDescent(p)
{
    lineSearchMethod = "armijo";
    //available values: golden, fibonacci, armijo
}
void    GradientWithLS::setLineSearch(string m)
{
    lineSearchMethod = m;
}

string  GradientWithLS::getLineSearch() const
{
    return lineSearchMethod;
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
    return myProblem->statFunmin(trialx);
}
double GradientWithLS::fib(int k)
{
    return (pow(1+sqrt(5),k+1)-pow(1-sqrt(5),k+1))/(pow(2,k+1)*sqrt(5));
}

void    GradientWithLS::fibonacciSearch(double &a,double &b)
{

    int iteration = 2;
    while(true)
    {
          double phi = fib(iteration)/fib(iteration+1);
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
void    GradientWithLS::armijoSerch(double &a)
{
    double f0 = myProblem->statFunmin(xpoint);
    double beta =0.001;
    double t = 0.5;
    int iteration = 0;
    do
    {
            a = a * t;
            iteration++;
            if(iteration>=20) break;
    }while(fl(a)>f0-a*beta*myProblem->grms(xpoint));

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
    if(lineSearchMethod=="golden")
    {
        double lambda = rate;
        double a = lambda * 0.9;
        double b = lambda * 1.1;
        goldenSearch(a,b);
        rate = a;
    }
    else
    if(lineSearchMethod=="fibonacci")
    {
        double lambda = rate;
        double a = lambda * 0.9;
        double b = lambda * 1.1;
        fibonacciSearch(a,b);
        rate = a;
    }
    else
    {
        double lambda  = 2;
        armijoSerch(lambda);
        rate = lambda;
    }
}
