#ifndef RASTRIGINPROBLEM_H
#define RASTRIGINPROBLEM_H
# include <problem.h>

class RastriginProblem : public Problem
{
public:
    RastriginProblem();
    double funmin(Data &x);
    Data gradient(Data &x);
};


#endif // RASTRIGINPROBLEM_H
