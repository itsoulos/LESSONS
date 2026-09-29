#ifndef SIMANMETHOD_H
#define SIMANMETHOD_H
# include "problem.h"
class SimanMethod
{
private:
    double T0;
    Data xpoint;
    double ypoint;
    int neps;
    double eps;
    Problem *myProblem;
public:
    SimanMethod(Problem *p);
    void    setT0(double t);
    double  getT0() const;
    void    setNeps(int n);
    int     getNeps() const;
    void    setEpsilon(double e);
    double  getEpsilon() const;
    void    Solve();
    Data    getX();
    void    setPoint(Data &x,double y);
    ~SimanMethod();
};
#endif // SIMANMETHOD_H
