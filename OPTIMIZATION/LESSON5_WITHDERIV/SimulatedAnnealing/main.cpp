# include "rastriginproblem.h"
# include "gradientwithls.h"
# include "simanmethod.h"
# include "statistics.h"


int main()
{
    const int times =30;
    Statistics stat;

    for(int t=1;t<=times;t++)
    {
        srand(t);
        RastriginProblem p;
        SimanMethod method(&p);
        method.Solve();
        GradientDescent gd(&p);
        Data xx = p.getBestx();
        double yy = p.getBesty();
        gd.setPoint(xx,yy);
        gd.Solve();
        stat.addProblem(&p);
    }


    stat.printStatistics();
    return 0;
}
