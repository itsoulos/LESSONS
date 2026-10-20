#ifndef ROLLMETHOD_H
#define ROLLMETHOD_H
# include <problem.h>

class RollMethod
{
private:
    Data step;
    Data xsample;
    double ysample;
    int maxiters=100;
    Problem *myProblem;
public:
    RollMethod(Problem *p,double stepInitValue=0.01);
    void    setMaxIters(int n);
    void    setStepArray(const Data &stepValues);
    void    Solve();
    Data    getBestX() const;
    double  getBestY() const;
    ~RollMethod();
};

#endif // ROLLMETHOD_H
