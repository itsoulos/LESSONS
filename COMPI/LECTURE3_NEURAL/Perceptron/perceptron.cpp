#include "perceptron.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
Perceptron::Perceptron()
{
    n=0.1;
    emax=100;
    trainSet=NULL;
    testSet=NULL;
}


Perceptron::Perceptron(Dataset *tr,Dataset *tt)
{
    n=0.1;
    emax=100;
   setTrainSet(tr);
   setTestSet(tt);
}
void    Perceptron::setTrainSet(Dataset *t)
{
    trainSet=t;

    //t->dimension() einai to plithos ton xaraktiristikon
    //px sto wine einai 13.
    //to +1 einai epeidi exo kai to bias (parametros b sto pdf)
    weight.resize(t->dimension()+1);
    //randomize weights
    int i;

    for(i=0;i<weight.size();i++)
        //epistrefei arxika times sto [-1,1]
        //pollaplasiazo to [-1,1] me 0.1 kai ara o tyxaios tha einai sto diastima [-0.1,0.1]
        weight[i]=0.1 *(rand() * 1.0/RAND_MAX);
}

void    Perceptron::setTestSet(Dataset *t)
{
    testSet=t;
}

void    Perceptron::setN(double mn)
{
    if(mn>0 && mn<1) n=mn;
}

double  Perceptron::getN() const
{
    return n;
}

void    Perceptron::setEmax(int e)
{
    if(e>0) emax=e;
}

int     Perceptron::getEmax() const
{
    return emax;
}


//esoteriko ginomeno pinakon

//w^T*x=enas arithmos
double  Perceptron::product(Data x,Data y)
{
    double sum=0.0;
    int i;
    for(i=0;i<x.size();i++)
        sum=sum+x[i]*y[i];
    return sum;
}

void  Perceptron::train()
{
    //e einai i epochi
    int e;
    for(e=1;e<=emax;e++)
    {
        int i;

        //kratao ta palia bari gia na elexo an tha metablithoun i oxi
        Data oldWeights=weight;

        //pername ta protypa ena pros ena



        for(i=0;i<trainSet->count();i++)
        {

            //pairno to train protypo stin thesi i
            Data pattern=trainSet->getXPoint(i);
            //pairno tin pragmatiki exo to y(x) apo to pdf
            double yx=trainSet->getYPoint(i);

            //to kanoniko protypo einai to x=(x0,x1,....,x(n-1))
            //ta bari omos einai w=(w0,w1,.....,w(n)) giati stin
            //thesi n exo kai to bias

            //gia na einai loipon sosto to esoteriko ginomeno bazo
            //sto telos tou x kai to 1
            //bazo sto telos tou protypo to +1
           pattern.push_back(1.0);
            double ux=product(pattern,weight);

            //upologizo to o(x) apo to pdf
            double ox=ux>0?1.0:-1.0;
            int j;

            //kano update ta weight
            for(j=0;j<weight.size();j++)
                weight[j]=weight[j]+n*(yx-ox)*pattern[j];
        }

        //ypologizo tin diafora palaion kai neon varon
        double dist=distance(oldWeights,weight);
        if(dist<1e-5) break;
    }
}

double  Perceptron::distance(Data x,Data y)
{
    double sum=0.0;
    int i;
    for(i=0;i<x.size();i++)
        sum=sum+(x[i]-y[i])*(x[i]-y[i]);
    return sum;
}

double  Perceptron::getClass(Data pattern)
{
    pattern.push_back(1.0);
    double ux=product(pattern,weight);
    double ox=ux>0?1.0:-1.0;
    return ox;
}

//ypologizo poso xano apo ta test protypa
double  Perceptron::testError()
{
    int i;
    //einai posa xano to missed
    int missed=0;
    for(i=0;i<testSet->count();i++)
    {

        //yx i pragmatiki exodos
        double yx=testSet->getYPoint(i);
        //px einai i exodos tou perceptron
        double px=getClass(testSet->getXPoint(i));
        //metrao diafora

        if(fabs(yx-px)>1e-5) missed++;
    }
    return missed*100.0/testSet->count();
}
