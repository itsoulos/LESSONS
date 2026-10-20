#ifndef PROBLEM_H
#define PROBLEM_H


#include <vector>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Data;
typedef vector<Data> Matrix;

class Problem
{
protected:
    int dimension;
    Data left, right;
    int functioncalls;
public:
    Problem(int n);
    int getDimension() const;
    Data getSample();
    void setLeftMargin(Data &x);
    void setRightMargin(Data &x);
    Data getLeftMargin() const;
    Data getRightMargin() const;
    virtual double funmin(Data &x) = 0;
    virtual Data gradient(Data &x) = 0;
    virtual double statFunmin(Data &x);
    double grms(Data &x);
    void    resetFunctionCalls();
    int     getFunctionCalls() const;
    ~Problem();
};
#endif // PROBLEM_H
