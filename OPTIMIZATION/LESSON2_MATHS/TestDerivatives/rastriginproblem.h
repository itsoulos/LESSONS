#ifndef RASTRIGINPROBLEM_H
#define RASTRIGINPROBLEM_H
# include <vector>
using namespace std;

typedef vector<double> Data;
class RastriginProblem
{
private:
    int dimension;
    Data left,right;
    int  functionCalls;
public:
    RastriginProblem();
    double  funmin(Data &x);
    Data    gradient(Data &x);
    Data    getRandomSample();
    Data    finiteGradient1(Data &x);
    Data    finiteGradient2(Data &x);
    double  grms(Data &g);

    int     getDimension()   const;
    Data    getLeftMargin()  const;
    Data    getRightMargin() const;
    int     getFunctionCalls() const;
    void    resetFunctionCalls();
    ~RastriginProblem();
};

#endif // RASTRIGINPROBLEM_H
