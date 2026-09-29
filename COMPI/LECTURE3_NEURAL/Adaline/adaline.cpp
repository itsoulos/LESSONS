#include "adaline.h"
# include <stdlib.h>
# include <math.h>
Adaline::Adaline()
{
    n=0.1;
    maxepochs=100;
}
static int indexOf(Data &x,double v);

void    Adaline::setTrainSet(Dataset *t)
{
    trainSet=t;

    //bazo +1 gia to bias
    weight.resize(trainSet->dimension()+1);
    int i;
    for(i=0;i<weight.size();i++)
    {
        weight[i]=0.1 * (rand() *1.0/RAND_MAX);
    }

    //edo brisko poies monadikes katigories exei to dataset
    for(i=0;i<trainSet->count();i++)
    {
        double y=trainSet->getYPoint(i);
        if(indexOf(classVector,y)==-1)
            classVector.push_back(y);
    }
}

static int indexOf(Data &x,double v)
{
    for(int i=0;i<x.size();i++)
        if(fabs(x[i]-v)<1e-5) return i;
    return -1;
}
void    Adaline::setTestSet(Dataset *t)
{
    testSet=t;
}

void    Adaline::setN(double mn)
{
    if(mn>0 && mn<1) n=mn;
}

double  Adaline::getN() const
{
    return n;
}

void    Adaline::setMaxEpochs(int e)
{
    if(e>0) maxepochs=e;
}

int     Adaline::getMaxEpochs() const
{
    return maxepochs;
}

void    Adaline::train()
{
    int k;

    //to k einai o metris epochon
    for(k=1;k<=maxepochs;k++)
    {
        int i;
        for(i=0;i<trainSet->count();i++)
        {
            //pairno to train protypo stin thesi i
            Data pattern=trainSet->getXPoint(i);
            //bazo +1 sto telos gia to bias
            //oste na mou bgei to esoteriko ginomeno
            pattern.push_back(1.0);

            //ypologizo w^T * pattern
            double u=getOutput(pattern);
            int j;
            //update ta weights
            for(j=0;j<weight.size();j++)
                weight[j]=weight[j]+n*(trainSet->getYPoint(i)-u)*pattern[j];
        }
        //edo ypologizo tin diafora
        //anamesa stin exodo kai stin pragmatiki exodo
        double e=getTrainError();
        if(e<1e-4) break;
    }
}

double Adaline::getTrainError()
{
    double sum=0.0;
    int i;
    for(i=0;i<trainSet->count();i++)
    {
        Data pattern=trainSet->getXPoint(i);
        pattern.push_back(1.0);
        double u=getOutput(pattern);
        double y=trainSet->getYPoint(i);
        sum+=(u-y)*(u-y);
    }
    return sum/trainSet->count();
}

double  Adaline::getTestError()
{
    double sum=0.0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data pattern=testSet->getXPoint(i);
        pattern.push_back(1.0);
        double u=getOutput(pattern);
        double y=testSet->getYPoint(i);
        sum+=(u-y)*(u-y);
    }
    return sum/testSet->count();
}

double  Adaline::getClassError()
{
    int missed=0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data pattern=testSet->getXPoint(i);
        pattern.push_back(1.0);
        double d=getClass(pattern);
        double y=testSet->getYPoint(i);
        if(fabs(d-y)>1e-5) missed++;
    }
    return missed * 100.0/testSet->count();
}

double  Adaline::getOutput(Data pattern)
{
    double f=product(pattern,weight);
    return f;
}

double  Adaline::getClass(Data pattern)
{
    double f=product(pattern,weight);
    int minClass=-1;
    double minDist=1e+10;
    int i;
    for(i=0;i<classVector.size();i++)
    {
        double dist=fabs(classVector[i]-f);
        if(dist<minDist)
        {
            minClass=i;
            minDist=dist;
        }
    }
    return classVector[minClass];
}


double  Adaline::product(Data x, Data y)
{
    int i;
    double s=0.0;
    for(i=0;i<x.size();i++)
        s+=x[i]*y[i];
    return s;
}
