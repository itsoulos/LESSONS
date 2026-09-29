#ifndef PROBLEM_H
#define PROBLEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Data;
typedef vector<Data> Matrix;

class Problem
{
protected:
    int dimension;
    Data left, right;
    Data bestx;
    double besty;
    int functionCalls;
public:
    Problem(int n);
    int getDimension() const;
    virtual Data getSample();
    void setLeftMargin(Data &x);
    void setRightMargin(Data &x);
    Data getLeftMargin() const;
    Data getRightMargin() const;
    virtual double funmin(Data &x) = 0;
    virtual Data gradient(Data &x) = 0;
    /**
     * @brief statFunmin Kalei prota tin funmin(x)
     * kai diatirei to bestvalue kai kanei update
     * ta function calls
     * @param x
     */
    double statFunmin(Data &x);
    double grms(Data &x);
    Data    getBestx() const;
    double  getBesty() const;
    int     getFunctionCalls() const;
    void    setDimension(int n);
    ~Problem();
};

#endif // PROBLEM_H
