#ifndef GRADIENTWITHLS_H
#define GRADIENTWITHLS_H

#include "gradientdescent.h"

class GradientWithLS :public GradientDescent
{
private:
    string lineSearchMethod;
public:
    GradientWithLS(Problem *p);
    void    setLineSearch(string m);
    string  getLineSearch() const;
    double fib(int k);
    double  fl(double h);
    void    goldenSearch(double &a,double &b);
    void    fibonacciSearch(double &a,double &b);
    void    armijoSerch(double &a);
    virtual void    updateRate();

};

#endif // GRADIENTWITHLS_H
