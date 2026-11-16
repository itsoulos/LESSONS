#include "gradientdescent.h"


GradientDescent::GradientDescent(Problem *p)
{
    myProblem = p;
    rate = 0.001;
    xpoint = myProblem->getSample();
    ypoint = myProblem->statFunmin(xpoint);
}


void    GradientDescent::setRate(double r)
{
    if(r>0) rate = r;
}

double  GradientDescent::getRate() const
{
    return rate;
}

void    GradientDescent::updateRate()
{
    //nothing here
}
void   GradientDescent::setPoint(Data &x,double &y)
{
    xpoint = x;
    ypoint = y;
}

Data    GradientDescent::getBestx()
{
    return xpoint;
}

double    GradientDescent::getBesty()
{
    return ypoint;
}
void    GradientDescent::updatePoint()
{
    Data g = myProblem->gradient(xpoint);
    unsigned int i;
    for(i=0;i<g.size();i++)
        xpoint[i]=xpoint[i]-rate * g[i];
    ypoint=myProblem->statFunmin(xpoint);
}

void    GradientDescent::Solve()
{
    int k=0;
    while(true)
    {
        updateRate();
        updatePoint();
        k=k+1;
        if(myProblem->grms(xpoint)<1e-3) break;

    }
}
GradientDescent::~GradientDescent()
{
    //nothing here
}
