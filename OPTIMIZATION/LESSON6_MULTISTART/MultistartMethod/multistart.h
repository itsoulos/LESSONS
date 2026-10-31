#ifndef MULTISTART_H
#define MULTISTART_H
# include "problem.h"
# include "gradientwithls.h"
class Multistart
{
private:
    Problem *myProblem;
    int     nsamples;
    Data    bestx;
    double  besty;
    int     iter;
    int     maxiters;
public:
    Multistart(Problem *p);
    void setNsamples(int n);
    int  getNsamples() const;
    void    setMaxiters(int m);
    int     getMaxiters() const;
    void    Step();
    void    Solve();
    Data    getBestx();
    double  getBesty();
    bool    Terminated();
    ~Multistart();
};
#endif // MULTISTART_H
