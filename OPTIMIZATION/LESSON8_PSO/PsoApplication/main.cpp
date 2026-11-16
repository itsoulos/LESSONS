#include "psomethod.h"
# include "statistics.h"

class RastriginProblem : public Problem
{
public:
    RastriginProblem();
    double funmin(Data &x);
    Data gradient(Data &x);
};

RastriginProblem::RastriginProblem()
    : Problem(2)
{
    Data l, r;
    l.resize(2);
    r.resize(2);
    for (int i = 0; i < 2; i++)
    {
        l[i] = -1.0;
        r[i] = 1.0;
    }
    setLeftMargin(l);
    setRightMargin(r);
}

double RastriginProblem::funmin(Data &x)
{
    return x[0] * x[0] + x[1] * x[1] - cos(18.0 * x[0]) - cos(18.0 * x[1]);
}

Data RastriginProblem::gradient(Data &x)
{
    Data g;
    g.resize(2);
    g[0] = 2.0 * x[0] + 18.0 * sin(18.0 * x[0]);
    g[1] = 2.0 * x[1] + 18.0 * sin(18.0 * x[1]);
    return g;
}

class Test2nProblem : public Problem
{
public:
    Test2nProblem(int n);
    double funmin(Data &x);
    Data gradient(Data &x);
};

Test2nProblem::Test2nProblem(int n)
    :Problem(n)
{
    Data l, r;
    l.resize(n);
    r.resize(n);
    for (int i = 0; i < n; i++)
    {
        l[i] = -5.0;
        r[i] = 5.0;
    }
    setLeftMargin(l);
    setRightMargin(r);
}

double Test2nProblem::funmin(Data &x)
{
    double sum=0.0;
    for(int i=0;i<dimension;i++)
      sum+=0.5 * (pow(x[i],4.0)-16.0 * pow(x[i],2.0)+5.0*x[i]);
   return sum;
}

Data Test2nProblem::gradient(Data &x)
{
    Data g;
    g.resize(dimension);
    for(int i=0;i<dimension;i++)
        {
            g[i]=0.5 * (4.0*pow(x[i],3.0)-32*x[i]+5.0);
        }
    return g;
}

int main()
{
    const int times =30;
    Statistics stat;

    for(int t=1;t<=times;t++)
    {
        srand(t);
       Test2nProblem p(5);
        PsoMethod method(&p);
        method.Solve();
        stat.addProblem(&p);

    }


    stat.printStatistics();
    return 0;
}
