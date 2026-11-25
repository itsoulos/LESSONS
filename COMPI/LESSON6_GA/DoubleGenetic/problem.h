#ifndef PROBLEM_H
#define PROBLEM_H

# include <QVector>
typedef QVector<double> Data;

class Problem
{
private:
    int dimension;
    Data leftMargin,rightMargin;
public:
    Problem(int d);
    void setLeftMargin(Data x);
    Data getLeftMargin();
    void setRightMargin(Data x);
    Data getRightMargin();
    int  getDimension();
    Data    getSample();
    void    mutate(Data &x,int pos);
    virtual double funmin(Data x)=0;
};

#endif // PROBLEM_H
