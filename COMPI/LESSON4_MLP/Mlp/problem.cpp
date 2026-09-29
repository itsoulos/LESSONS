#include "problem.h"


Problem::Problem(int n)
{
    setDimension(n);
}

void    Problem::setDimension(int n)
{
    dimension = n;
    left.resize(dimension);
    right.resize(dimension);
    besty = 1e+100;
    functionCalls = 0;
}
double    Problem::statFunmin(Data &x)
{
    double y = funmin(x);
    if(y<besty)
    {
        besty = y;
        bestx = x;
    }
    ++functionCalls;
    return y;
}

Data    Problem::getBestx() const
{
    return bestx;
}

double  Problem::getBesty() const
{
    return besty;
}

int     Problem::getFunctionCalls() const
{
    return functionCalls;
}

int Problem::getDimension() const
{
    return dimension;
}

Data Problem::getSample()
{
    Data x;
    x.resize(dimension);
    double r;
    for (int i = 0; i < dimension; i++)
    {
        r = rand()*1.0/RAND_MAX;
        x[i] = left[i] + (right[i] - left[i]) * r;

    }
    return x;
}
void Problem::setLeftMargin(Data &x)
{
    left = x;
}

void Problem::setRightMargin(Data &x)
{
    right = x;
}
Data Problem::getLeftMargin() const
{
    return left;
}

Data Problem::getRightMargin() const
{
    return right;
}

double Problem::grms(Data &x)
{
    Data g = gradient(x);
    int i;
    double s = 0.0;
    for (i = 0; i < x.size(); i++)
        s = s + g[i] * g[i];
    return sqrt(s / x.size());
}

Problem::~Problem()
{
}
