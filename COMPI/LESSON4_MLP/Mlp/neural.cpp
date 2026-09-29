#include "neural.h"
# include "gradientdescent.h"
# include "gradientwithls.h"
# include "simanmethod.h"
# include <math.h>
Neural::Neural()
    :Problem(1)
{
    learningRate=0.01;
    nweight=1;
    maxepochs=500;
}

double Neural::funmin(Data &x)
{
   setWeights(x);
   return getTrainError();
}

Data Neural::getSample()
{
    Data x;
    x.resize(weight.size());
    for(int i=0;i<weight.size();i++)
        x[i]=0.1 *(2.0*rand()*1.0/RAND_MAX-1.0);
    return x;
}

Data Neural::gradient(Data &x)
{

    setWeights(x);
    return getDeriv();
}
void    Neural::setTrainMethod(string s)
{
    trainMethod = s;
}

string  Neural::getTrainmethod() const
{
    return trainMethod;
}

void    Neural::setTrainSet(Dataset *t)
{
    trainSet=t;

}

void    Neural::setTestSet(Dataset *t)
{
    testSet=t;
}

double  Neural::getLearningRate()
{
    return learningRate;
}

void    Neural::setLearningRate(double x)
{
    if(x>0 && x<1)
        learningRate=x;
}

int     Neural::getMaxEpochs()
{
    return maxepochs;
}

void    Neural::setMaxEpochs(int m)
{
    if(m>0)
        maxepochs=m;
}

void    Neural::setWeights(Data &w)
{
    weight=w;
}

Data    Neural::getWeights()
{
    return weight;
}

void    Neural::setNWeights(int N)
{
    //arxikopoihhsh baron
    nweight=N;
    weight.resize((trainSet->dimension()+2)*nweight);
    int i;
    for(i=0;i<weight.size();i++)
    {
        weight[i]=0.02* (rand() *1.0/RAND_MAX);
    }
    setDimension(weight.size());
    Data l,r;
    l.resize(weight.size());
    r.resize(weight.size());
    for(int i=0;i<weight.size();i++)
    {
        l[i]=-10.0;
        r[i]= 10.0;
    }
    setLeftMargin(l);
    setRightMargin(r);
}

double  Neural::sig(double x)
{
    return 1.0/(1.0+exp(-x));
}

double  Neural::sigder(double x)
{
    double s=sig(x);
    return s*(1.0-s);
}

double  Neural::getOuput(Data &x)
{
    //exodos tou diktyou
    double arg=0.0;
        double per=0.0;
        int nodes = weight.size()/(x.size()+2);
        int d = x.size();
        for(int i=1;i<=nodes;i++)
        {
            arg=0.0;
            for(int j=1;j<=d;j++)
            {
                int pos=(d+2)*i-(d+1)+j-1;
                arg+=weight[pos]*x[j-1];

            }
            arg+=weight[(d+2)*i-1];
            per+=weight[(d+2)*i-(d+1)-1]*sig(arg);
        }
        return per;
}

double  Neural::getClass(Data &pattern)
{
    double f=getOuput(pattern);
    return trainSet->getClass(f);
}

double  Neural::getTrainError()
{
    //sfalma ekpaideysis
    double sum=0.0;
    int i;
    for(i=0;i<trainSet->count();i++)
    {
        Data xx = trainSet->getXPoint(i);
        double ox=getOuput(xx);
        double yx=trainSet->getYPoint(i);
        sum+=(ox-yx)*(ox-yx);
    }
    return sum;
}

double  Neural::getTestError()
{
    //sfalma elegxou
    double sum=0.0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data xx = testSet->getXPoint(i);
        double ox=getOuput(xx);
        double yx=testSet->getYPoint(i);
        sum+=(ox-yx)*(ox-yx);
    }
    return sum;
}

double  Neural::getClassError()
{
    //sfalma katigoriopoihshs
    int missed=0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data pattern=testSet->getXPoint(i);
        double d=getClass(pattern);
        double y=testSet->getYPoint(i);

        if(fabs(d-y)>1e-5) missed++;
    }
    return missed * 100.0/testSet->count();
}

Data    Neural::getDerivAtPoint(Data &x)
{

    //paragogos ana simeio
    double arg;
        double f,f2;
        int nodes = weight.size()/(x.size()+2);
        int d = x.size();
        Data G;
        G.resize(weight.size());

        for(int i=1;i<=nodes;i++)
        {
            arg = 0.0;
            for(int j=1;j<=d;j++)
            {
                arg+=weight[(d+2)*i-(d+1)+j-1]*x[j-1];
            }
            arg+=weight[(d+2)*i-1];
            f=sig(arg);
            f2=f*(1.0-f);
            G[(d+2)*i-1]=weight[(d+2)*i-(d+1)-1]*f2;
            G[(d+2)*i-(d+1)-1]=f;
            for(int k=1;k<=d;k++)
            {
                G[(d+2)*i-(d+1)+k-1]=
                    x[k-1]*f2*weight[(d+2)*i-(d+1)-1];
            }
        }
        return G;
}

Data    Neural::getDeriv()
{
    //parogogos
    Data g;
    g.resize(weight.size());
    int i,j;
    for(i=0;i<g.size();i++)
        g[i]=0.0;

    for(i=0;i<trainSet->count();i++)
    {
        Data x=trainSet->getXPoint(i);
        Data gx=getDerivAtPoint(x);
        double ox=getOuput(x);
        double yx=trainSet->getYPoint(i);
        for(j=0;j<g.size();j++)
            g[j]+=2.0*(ox-yx)*gx[j];
    }
    return g;
}

void    Neural::train()
{
    if(trainMethod == "gd")
    {
        GradientDescent gd(dynamic_cast<Problem *>(this));

        gd.setRate(getLearningRate());
        gd.setMaxIterations(getMaxEpochs());
        gd.Solve();
        double f;
        gd.getPoint(weight,f);
    }
    else
    if(trainMethod == "gdwithls")
    {
        GradientWithLS gd(dynamic_cast<Problem *>(this));

        gd.setRate(getLearningRate());
        gd.setMaxIterations(getMaxEpochs());
        gd.Solve();
        double f;
        gd.getPoint(weight,f);
    }
    else
    if(trainMethod=="siman")
    {
        SimanMethod method(dynamic_cast<Problem *>(this));

        method.Solve();
        weight = method.getX();
        GradientWithLS gd(dynamic_cast<Problem *>(this));

        gd.setRate(getLearningRate());
        gd.setMaxIterations(getMaxEpochs());

        gd.setPoint(weight,getTrainError());
        gd.Solve();
        double f;
        gd.getPoint(weight,f);

    }

}

Neural::~Neural()
{

}
