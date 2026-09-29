#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H
# include "problem.h"

class GradientDescent
{
protected:
    double rate;
    Data xpoint;
    double ypoint;
    Problem *myProblem;
    int maxiters=500;
public:
    GradientDescent(Problem *p);
    void setRate(double r);
    double getRate() const;
    void    setMaxIterations(int m);
    int     getMaxIterations() const;
    void    getPoint(Data &x,double &y);

    virtual void    updateRate();
    virtual void    updatePoint();
    void    setPoint(Data &x,double y);
    void    Solve();
    ~GradientDescent();
};
#endif // GRADIENTDESCENT_H
