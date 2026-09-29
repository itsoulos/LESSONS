#include <QCoreApplication>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <vector>
using namespace std;
typedef vector<double> Data;

double randomDouble()
{
    return rand() *1.0/RAND_MAX;
}

Data randomArray(int size)
{
    Data x;
    x.resize(size);
    for(int i=0;i<size;i++)
        x[i]=20.0*randomDouble()-10.0; //range is [-10,10]
    return x;

}

void printArray(Data &x)
{
    printf("X=");
    for(int i=0;i<x.size();i++)
        printf("%6.2lf",x[i]);
    printf("\n");
}

//epistrefei ta stoixeia me timi pano apo 5
Data subArray(Data &x)
{
    Data y;
    for(int i=0;i<x.size();i++)
    {
        if(x[i]>=5)
            y.push_back(x[i]);
    }
    return y;
}

double maxArray(Data &x)
{
    double max=x[0];
    for(int i=0;i<x.size();i++)
        if(x[i]>max) max=x[i];
    return max;
}


double avgArray(Data &x)
{
    double sum=0.0;
    for(int i=0;i<x.size();i++)
        sum+=x[i];
    return sum/x.size();
}

void permutate(Data &x)
{
    for(int i=0;i<x.size();i++)
    {
        int pos1=i;
        int pos2=rand()%x.size();
        double t=x[pos1];
        x[pos1]=x[pos2];
        x[pos2]=t;
    }
}

int main(int argc, char *argv[])
{
    srand(100);
    Data x=randomArray(10);
    printArray(x);
    Data y=subArray(x);
    printArray(y);
    permutate(x);
    printArray(x);
    return 0;
}
