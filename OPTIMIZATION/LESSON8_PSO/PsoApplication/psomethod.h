#ifndef PSOMETHOD_H
#define PSOMETHOD_H
# include "problem.h"
# include "collection.h"
# include "gradientwithls.h"
class PsoMethod
{
private:
    Problem *myProblem;
    Collection particle;
    Collection  bestParticle;
    Collection velocity;
    int     particleCount;
    double inertia;
    int     iter;
    int     maxiters;
    Data    bestx;
    double  besty;
public:
    PsoMethod(Problem *p);
    void    setMaxiters(int i);
    int     getMaxiters() const;
    void    setParticleCount(int c);
    int     getParticleCount() const;
    Data    getBestx();
    double  getBesty();
    bool    Terminated();
    void    Step();
    void    Solve();
    ~PsoMethod();
};

#endif // PSOMETHOD_H
