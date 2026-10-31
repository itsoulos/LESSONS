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
public:
    GradientDescent(Problem *p);
    void setPoint(Data &x,double y);
    Data getBestx() const;
    double getBesty() const;
    void setRate(double r);
    double getRate() const;
    virtual void    updateRate();
    virtual void    updatePoint();
    void    Solve();
    ~GradientDescent();
};

#endif // GRADIENTDESCENT_H
