#ifndef MULTISTART_H
#define MULTISTART_H
# include "problem.h"
# include "collection.h"
class Multistart
{
private:
    Problem *myProblem;
    int     nsamples;
    Data    bestx;
    double  besty;
    int     iter;
    int     maxiters;
    Collection minima;
    string terminationRule; //posible values: iters, kan, doublebox
    //for doublebox
    double x1,x2;
    int oldminima;
    double stopat;
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
    void    setTerminationRule(string s);
    string  getTerminationRule() const;
    ~Multistart();
};
#endif // MULTISTART_H
