#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
# include <rastriginproblem.h>
# include <simanmethod.h>
#include <vector>
#include <iostream>
using namespace std;

int main()
{
    RastriginProblem p;
    int total_calls = 0;
    Data minimaFound;
    const int iters=30;
    srand(1000);
    for(int i=1;i<=iters;i++)
    {
        p.resetFunctionCalls();
        SimanMethod sim(&p);
        sim.Solve();
        total_calls+=p.getFunctionCalls();
        minimaFound.push_back(sim.getY());
    }
    for(int i=0;i<iters;i++)
    {
        printf("Minimum[%4d]=%20.10lg\n",i,minimaFound[i]);
    }
    printf("Total function calls = %5d\n",total_calls);
    return 0;
}
