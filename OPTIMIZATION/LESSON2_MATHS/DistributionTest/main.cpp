# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include <random>
using namespace std;

std::random_device seed;
std::mt19937 generator(seed());
const double k_T = 0.1;
gamma_distribution<double> maxwell(3./2., k_T);

double randNumber()
{
    return rand()*1.0/RAND_MAX;
}

double uniformNumber(double a, double b)
{
    return a + (b-a)*randNumber();
}


double triangularNumber(double a,double b)
{
    double c= (a+b)/2.0;
    double F = (c-a) / (b-a);
    double U = randNumber();
    if (U <= F)
        return a + sqrt(U * (b - a) * (c - a));
    else
        return b - sqrt((1. - U) * (b - a) * (b - c));
}

double maxwellNumber(double a,double b)
{

    double r=maxwell(generator);
    return a+(b-a)*r;
}

int main()
{
    //try different number of points
    const int npoints = 10000;
    double uniformMean = 0.0;
    double triangularMean = 0.0;
    double maxwellMean = 0.0;
    double xx1=0.0,xx2=0.0;

    for(int i=0;i<npoints;i++)
    {
        double x= uniformNumber(10,20);
        uniformMean+=x;
        xx1+=x;
        xx2+=x*x;
    }
    uniformMean/=npoints;
    double stdMean =sqrt(1.0/npoints*((xx2/npoints)*(xx2/npoints)-xx1/npoints));
    printf("Uniform mean = %lf  stdMean  =%lf \n",uniformMean,stdMean);

    xx1=0.0;xx2=0.0;
    for(int i=0;i<npoints;i++)
    {
        double x= triangularNumber(10,20);
        triangularMean+=x;
        xx1+=x;
        xx2+=x*x;
    }
    triangularMean/=npoints;
    stdMean =sqrt(1.0/npoints*((xx2/npoints)*(xx2/npoints)-xx1/npoints));
    printf("Triangular mean = %lf Triangular std =%lf\n",triangularMean,stdMean);

    xx1=0.0;xx2=0.0;
    for(int i=0;i<npoints;i++)
    {
        double x= maxwellNumber(10,20);
        maxwellMean+=x;
        xx1+=x;
        xx2+=x*x;
    }
    maxwellMean/=npoints;
    stdMean =sqrt(1.0/npoints*((xx2/npoints)*(xx2/npoints)-xx1/npoints));
    printf("Maxwell mean = %lf Maxwell std =%lf\n",maxwellMean,stdMean);

    return 0;
}
