#ifndef GRADIENTWITHLS_H
#define GRADIENTWITHLS_H
# include "gradientdescent.h"
class GradientWithLS :public GradientDescent
{
public:
    GradientWithLS(Problem *p);
    double  fl(double h);
    void    goldenSearch(double &a,double &b);
    virtual void    updateRate();

};


#endif // GRADIENTWITHLS_H
