# include "rastriginproblem.h"
# include "statistics.h"
# include "purerandomsearch.h"

int main()
{
    const int times =30;
    Statistics stat;
    for(int t=1;t<=times;t++)
    {
        srand(t);
        RastriginProblem p;
        PureRandomSearch method(&p);
        method.Solve();
        stat.addProblem(&p);
    }
    stat.printStatistics();
    return 0;
}
