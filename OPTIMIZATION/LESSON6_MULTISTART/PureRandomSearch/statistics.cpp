#include "statistics.h"

Statistics::Statistics()
{
    bestyValue.resize(0);
    fcallsValue.resize(0);
}

void Statistics::addProblem(Problem *p)
{
    bestyValue.push_back(p->getBesty());
    fcallsValue.push_back(p->getFunctionCalls());
}

void Statistics::printStatistics()
{
    int n = (int)bestyValue.size();
    printf("Executions: %4d\n===================\n",n);
    int totalFcalls = 0;
    double miny = 1e+100;
    int timesMinimumFound = 0;
    for(int i=0;i<n;i++)
    {
        printf("RUN: %4d BEST VALUE: %20.10lg FUNCTION CALLS: %4d\n",
               i+1,bestyValue[i],fcallsValue[i]);
        totalFcalls+=fcallsValue[i];
        if(i==0 || bestyValue[i]<miny) miny=bestyValue[i];
    }
    for(int i=0;i<n;i++)
    {
        if(fabs(bestyValue[i]-miny)<1e-6)
            timesMinimumFound++;
    }
    printf("Average Function calls: %20.2lf\n",totalFcalls*1.0/n);
    printf("Minimum Function Value: %20.10lg\n",miny);
    printf("Percent Minimum  Found: %20.2lf%%\n",timesMinimumFound*100.0/n);
}

Statistics::~Statistics()
{

}
