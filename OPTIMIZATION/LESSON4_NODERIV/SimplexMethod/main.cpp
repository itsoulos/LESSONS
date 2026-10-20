#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
# include <rastriginproblem.h>
# include <simplexmethod.h>


int main()
{
    for(int i=1;i<=30;i++)
    {
    srand(i);
    RastriginProblem p;
    SimplexMethod method(&p);
    method.runAlgorithm();
    Data xx = method.getBestx();
    double gs = p.grms(xx);
    printf("GS = %20.10lg \n",gs);
    }

    //test run to save in file
    RastriginProblem p;
    SimplexMethod method(&p);
    method.enableSavePoints();
    method.runAlgorithm();
    return 0;
}
