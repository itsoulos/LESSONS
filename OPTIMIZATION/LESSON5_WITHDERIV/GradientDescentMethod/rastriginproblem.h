#ifndef RASTRIGINPROBLEM_H
#define RASTRIGINPROBLEM_H
# include "problem.h"

//x^2+y^2-cos(18x)-cos(18y)
class RastriginProblem : public Problem
{
public:
    RastriginProblem();
    double funmin(Data &x);
    Data gradient(Data &x);
};


#endif // RASTRIGINPROBLEM_H
