# include "rastriginproblem.h"
# include "gradientwithls.h"


int main()
{
    srand(100);
    RastriginProblem p;
    GradientDescent method(&p);
    method.setRate(0.00001);
    //GradientWithLS method(&p);
    method.Solve();

    return 0;
}
