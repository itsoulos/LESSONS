#include "gradientdescent.h"

GradientDescent::GradientDescent(Problem *p)
{
    myProblem = p;
    rate = 0.001;
    xpoint= p->getSample();
    ypoint = p->funmin(xpoint);
}

void    GradientDescent::setMaxIterations(int m)
{
    maxiters=m;
}

int     GradientDescent::getMaxIterations() const
{
    return maxiters;
}

void    GradientDescent::getPoint(Data &x,double &y)
{
    x = xpoint;
    y = ypoint;
}


void    GradientDescent::setPoint(Data &x, double y)
{
    xpoint = x;
    ypoint = y;

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

void    GradientDescent::updatePoint()
{
    Data g = myProblem->gradient(xpoint);
    unsigned int i;
    for(i=0;i<g.size();i++)
        xpoint[i]=xpoint[i]-rate * g[i];
    ypoint=myProblem->funmin(xpoint);
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
        printf("Iteration=%4d Value=%20.10lg\n",k,ypoint);
        if(k>=maxiters) break;
    }
}
GradientDescent::~GradientDescent()
{
    //nothing here
}
