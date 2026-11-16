#ifndef DEMETHOD_H
#define DEMETHOD_H
# include "problem.h"
# include "collection.h"
# include "gradientwithls.h"
class DeMethod
{
private:
    Problem *myProblem;
    Collection agent;
    int NP;
    double F;
    double CR;
    int maxiters;
    int iter;
    Data bestx;
    double besty;

public:
    DeMethod(Problem *p);
    void    setNP(int n);
    int     getNP() const;
    void    setF(double f);
    double  getF() const;
    void    setCR(double c);
    double  getCR() const;
    void    setMaxiters(int i);
    int     getMaxiters() const;
    Data    getBestx();
    double  getBesty();
    bool Terminated();
    void Step();
    void Solve();
    ~DeMethod();
};

#endif // DEMETHOD_H
