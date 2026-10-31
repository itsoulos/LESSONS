#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

# include "rastriginproblem.h"
# include "statistics.h"
# include "multistart.h"



int main()
{
    const int times =30;
    Statistics stat;

    for(int t=1;t<=times;t++)
    {
        srand(t);
        RastriginProblem p;
        Multistart method(&p);
        method.Solve();
        stat.addProblem(&p);
    }


    stat.printStatistics();
    return 0;
}
