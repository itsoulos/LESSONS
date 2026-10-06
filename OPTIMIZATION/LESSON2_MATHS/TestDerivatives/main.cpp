#include <stdio.h>
#include <rastriginproblem.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
using namespace std;
using namespace std::chrono;

int main()
{
    vector<Data> xsample;
    const int nsamples = 100000;
    xsample.resize(nsamples);

    RastriginProblem t1;
    for(int i=0;i<nsamples;i++)
    {
        xsample[i]=t1.getRandomSample();
    }
    //test1
    auto start1 = high_resolution_clock::now();
    double grms1 = 0.0;
    for(int i=0;i<nsamples;i++)
    {
        double fx = t1.funmin(xsample[i]);
        Data g = t1.gradient(xsample[i]);
        grms1+=t1.grms(g);
    }
    grms1/=nsamples;
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    printf("Time execution 1 : %ld GRMS: %20.10lf Function Calls: %d\n",
           duration1.count(),grms1,t1.getFunctionCalls());

    //test2
    t1.resetFunctionCalls();
    auto start2 = high_resolution_clock::now();
    double grms2 = 0.0;
    for(int i=0;i<nsamples;i++)
    {
        double fx = t1.funmin(xsample[i]);
        Data g = t1.finiteGradient1(xsample[i]);
        grms2+=t1.grms(g);
    }
    grms2/=nsamples;
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    printf("Time execution 2 : %ld GRMS: %20.10lf Function calls: %d\n",
           duration2.count(),grms2,t1.getFunctionCalls());
    //test3
    t1.resetFunctionCalls();
    auto start3 = high_resolution_clock::now();
    double grms3 = 0.0;
    for(int i=0;i<nsamples;i++)
    {
        double fx = t1.funmin(xsample[i]);
        Data g = t1.finiteGradient2(xsample[i]);
        grms3+=t1.grms(g);
    }
    grms3/=nsamples;
    auto stop3 = high_resolution_clock::now();
    auto duration3 = duration_cast<microseconds>(stop3 - start3);
    printf("Time execution 3 : %ld GRMS: %20.10lf Function calls: %d\n",
           duration3.count(),grms3,t1.getFunctionCalls());
    return 0;
}
