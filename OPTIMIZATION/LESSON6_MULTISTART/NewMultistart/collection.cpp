#include "collection.h"

Collection::Collection()
{
    xdata.resize(0);
    ydata.resize(0);
}

double  Collection::getDistance(Data &x,Data &y)
{
    double sum = 0.0;
    for(int i=0;i<x.size();i++)
    {
        sum+=(x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum/x.size());
}

void    Collection::getBestWorstValues(double &besty,double &worsty)
{
    besty = ydata[0];
    worsty = ydata[0];
    for(int i=0;i<(int)ydata.size();i++)
    {
        if(ydata[i]<besty) besty = ydata[i];
        if(ydata[i]>worsty) worsty = ydata[i];
    }
}

void    Collection::replacePoint(int pos,Data &x,double &y)
{
    for(int i=0;i<x.size();i++)
    xdata[pos][i]=x[i];
    ydata[pos]=y;
}

void    Collection::resizeInFraction(double fraction)
{
    for(int i=0;i<ydata.size();i++)
    {
        for(int j=0;j<ydata.size()-1;j++)
        {
            if(ydata[j+1]<ydata[j])
            {
                double t = ydata[j];
                ydata[j]=ydata[j+1];
                ydata[j+1]=t;
                Data tx = xdata[j];
                xdata[j]=xdata[j+1];
                xdata[j+1]=tx;
            }
        }
    }
    int newSize = (int)(fraction * xdata.size());
    xdata.resize(newSize);
    ydata.resize(newSize);
}

bool    Collection::isPointIn(Data x)
{
    for(int i=0;i<xdata.size();i++)
    {
        double d = getDistance(x,xdata[i]);
        if(d<1e-4) return true;
    }
    return false;
}

void    Collection::addPoint(Data &x,double &y)
{
    if(!isPointIn(x))
    {

        xdata.push_back(x);
        ydata.push_back(y);

    }
}

void    Collection::getPoint(int pos,Data &x,double &y)
{

    x=xdata[pos];
    y=ydata[pos];
}

bool    Collection::haveGraphMinima(Data &x,double &y,double distance)
{
    for(int i=0;i<ydata.size();i++)
    {
        if(ydata[i]<y && getDistance(x,xdata[i])<distance)
            return true;
    }
    return false;
}

int     Collection::getSize() const
{
    return xdata.size();
}

Collection::~Collection()
{
    //nothing here
}
