#include "psomethod.h"

PsoMethod::PsoMethod(Problem *p)
{
    myProblem = p;
    maxiters = 1000;
    particleCount = 500;
}

void    PsoMethod::setParticleCount(int c)
{
    if(c>0) particleCount = c;
}

int     PsoMethod::getParticleCount() const
{
    return particleCount;
}

void    PsoMethod::setMaxiters(int i)
{
    if(i>0) maxiters = i;
}

int     PsoMethod::getMaxiters() const
{
    return maxiters;
}

Data    PsoMethod::getBestx()
{
    return bestx;
}

double  PsoMethod::getBesty()
{
    return besty;
}

bool    PsoMethod::Terminated()
{
    double miny,maxy;
    particle.getBestWorstValues(miny,maxy);
    printf("PSO. Iter=%4d MINY=%20.10lf MAXY=%20.1lf\n",iter,miny,maxy);
    return iter>=maxiters || fabs(maxy-miny)<1e-4;
}

void    PsoMethod::Step()
{
    iter++;
    for(int i=0;i<particleCount;i++)
    {
        Data x;
        double y;
        particle.getPoint(i,x,y);
        Data vx;
        double vy;
        velocity.getPoint(i,vx,vy);
        Data bx;
        double by;
        bestParticle.getPoint(i,bx,by);
        int n = myProblem->getDimension();
        inertia =0.5 + (rand()*1.0/RAND_MAX)/2.0;

        for(int j=0;j<n;j++)
        {
            double r1 = rand() *1.0/RAND_MAX;
            double r2 = rand() *1.0/RAND_MAX;
            vx[j]=inertia * vx[j]+r1 * (bx[j]-x[j])+r2*(bestx[j]-x[j]);
        }

        //isos prepei na kanonikopoiithei i taxytita?
        for(int j=0;j<n;j++)
          {
            x[j]=x[j]+vx[j];
        }
        if(!myProblem->isPointIn(x)) continue; //skip
        velocity.replacePoint(i,vx,vy);
        y = myProblem->statFunmin(x);
        particle.replacePoint(i,x,y);
        if(y<by)
        {
            bestParticle.replacePoint(i,x,y);
        }
        if(y<besty)
        {
            bestx  = x ;
            besty  = y;
        }
    }
}

void    PsoMethod::Solve()
{
    iter = 0;
    for(int i=0;i<particleCount;i++)
    {
        Data x= myProblem->getSample();
        double y = myProblem->statFunmin(x);
        particle.addPoint(x,y);
        bestParticle.addPoint(x,y);
        if(i==0 || y<besty)
        {
            bestx = x;
            besty = y;
        }
        Data zero=x;

        for(int j=0;j<x.size();j++)
            zero[j]=rand()*1.0/RAND_MAX;
        double yzero =0;
        velocity.addPoint(zero,yzero);
    }
    do
    {
        Step();
    }while(!Terminated());
    //apply a local search to the best point
    GradientWithLS gd(myProblem);
    gd.setLineSearch("armijo");
    gd.setPoint(bestx,besty);
    gd.Solve();
    bestx = gd.getBestx();
    besty = gd.getBesty();
}

PsoMethod::~PsoMethod()
{
    //nothing here
}
