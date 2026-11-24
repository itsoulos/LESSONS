#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H
# include "problem.h"

class GradientDescent
{
protected:
    double rate;
    Data xpoint;
    double ypoint;
    int maxiters;
    Problem *myProblem;
public:
    GradientDescent(Problem *p);
    void setRate(double r);
    void    setMaxIters(int m);
    int     getMaxIters() const;
    double getRate() const;
    virtual void    updateRate();
    virtual void    updatePoint();
    void    setPoint(Data &x,double &y);
    Data    getBestx();
    double  getBesty();
    void    Solve();
    ~GradientDescent();
};
#endif // GRADIENTDESCENT_H
