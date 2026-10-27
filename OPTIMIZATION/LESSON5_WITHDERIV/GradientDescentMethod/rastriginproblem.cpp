#include "rastriginproblem.h"


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
