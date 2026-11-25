#include "route.h"

Route::Route(int c)
{
    cities=c;
    costArray.resize(cities);
    int i;
    for(i=0;i<cities;i++)
    {
        costArray[i].resize(cities);
        costArray[i].fill(0);
    }
}

void    Route::addCost(int start,int end,int value)
{
    costArray[start][end]=value;
    costArray[end][start]=value;
}

QVector<int>    Route::randomRoute()
{
    QVector<int> x;
    x.resize(cities);
    int i;
    for(i=0;i<cities;i++) x[i]=i;
    for(i=0;i<cities;i++)
    {
        int pos=rand() % cities;
        int t=x[i];
        x[i]=x[pos];
        x[pos]=t;
    }
    return x;
}

void    Route::mutateRoute(QVector<int> &x,int pos)
{
    int pos2=rand()%x.size();
    int t=x[pos2];
    x[pos2]=x[pos];
    x[pos]=t;
}

QVector<int>    Route::crossoverRoute(QVector<int> x1,QVector<int> x2)
{
    int pos1=rand() % x1.size();
    int pos2=rand() % x1.size();
    QVector<int> g;
    g.resize(x1.size());
    g.fill(-1);
    int i;
    for(i=pos1;i<=pos2;i++) g[i]=x1[i];
    for(i=0;i<x2.size();i++)
    {
        int p=g.indexOf(x2[i]);
        if(p!=-1) continue;
        int nextPos=g.indexOf(-1);
        g[nextPos]=x2[i];
    }
    return g;
}

int Route::cost(QVector<int> x)
{
   int sum=0;
   int i;
   for(i=0;i<x.size()-1;i++)
       sum+=costArray[x[i]][x[i+1]];
   return sum;
}

int  Route::getCities()
{
    return cities;
}
