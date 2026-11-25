#include "problem.h"

Problem::Problem(int d)
{
    dimension=d;
}

void    Problem::setLeftMargin(Data x)
{
    leftMargin=x;
}

Data    Problem::getLeftMargin()
{
    return leftMargin;
}

void    Problem::setRightMargin(Data x)
{
    rightMargin=x;
}

Data    Problem::getRightMargin()
{
    return rightMargin;
}

int     Problem::getDimension()
{
    return dimension;
}

Data    Problem::getSample()
{
    Data g;
    g.resize(dimension);
    int i;
    for(i=0;i<dimension;i++)
        g[i]=leftMargin[i]+(rand()*1.0/RAND_MAX)*(rightMargin[i]-leftMargin[i]);
    return g;
}


void    Problem::mutate(Data &x,int pos)
{
    double r=rand() *1.0/RAND_MAX;
    x[pos]=leftMargin[pos]+r*(rightMargin[pos]-leftMargin[pos]);
}
