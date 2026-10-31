#ifndef PURERANDOMSEARCH_H
#define PURERANDOMSEARCH_H
# include "problem.h"

class PureRandomSearch
{
private:
    Problem *myProblem;
    int     nsamples;
    Data    bestx;
    double  besty;
    int     iter;
    int     maxiters;
public:
    PureRandomSearch(Problem *p);
    void setNsamples(int n);
    int  getNsamples() const;
    void    setMaxiters(int m);
    int     getMaxiters() const;
    void    Step();
    void    Solve();
    Data    getBestx();
    double  getBesty();
    bool    Terminated();
    ~PureRandomSearch();
};
#endif // PURERANDOMSEARCH_H
