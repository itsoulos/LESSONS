# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include <cmath>
#include <functional>
#include <stdexcept>
# include <vector>
using namespace std;

float sumFloat()
{
    float one=1.0;
    float e=1e-12;
    int i;
    float sum=0.0;
    for(i=1;i<=10000;i++)
        sum+=(one+e);
    return sum;
}

double sumDouble()
{
    double one=1.0;
    double e=1e-12;
    int i;
    double sum=0.0;
    for(i=1;i<=10000;i++)
        sum+=(one+e);
    return sum;
}

void ask1()
{
    float f=sumFloat();
    double d= sumDouble();
    printf("Sums: %20.10f %20.10lf\n",f,d);
}
double bisection(function<double(double)> f,
                 double a, double b,
                 double tol = 1e-8,
                 int maxiter = 1000)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) return a;
    if (fb == 0.0) return b;

    if (fa * fb > 0.0)
        return -1.0;

    for (int i = 0; i < maxiter; i++)
    {
        double c = a + (b - a) / 2.0;
        double fc = f(c);

        if (fabs(fc) < tol ||
            (b - a) / 2.0 < tol)
            return c;

        if ((fa < 0 && fc > 0) ||
            (fa > 0 && fc < 0))
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    return a + (b - a) / 2.0;
}

double newton(function<double(double)> f,
              function<double(double)> df,
              double x,
              double tol = 1e-8,
              int maxiter = 1000)
{
    for (int i = 0; i < maxiter; i++)
    {
        double fx = f(x);

        if (fabs(fx) < tol)
            return x;

        double dfx = df(x);

        if (fabs(dfx) < 1e-14)
            return -1.0;

        double xnew = x - fx / dfx;

        if (!isfinite(xnew))
            return -1.0;

        if (fabs(xnew - x) < tol)
            return xnew;

        x = xnew;
    }

     return -1.0;
}

double function1(double x)
{
    return exp(x)+x-5.0;
}

double function2(double x)
{
    return x*sin(x*x);
}

double function2Derivative(double x)
{
    return sin(x*x)+x*2*x*cos(x*x);
}

void ask2()
{
    double root = bisection(function1,1.0,10.0,1e-5);
    printf("Root = %lf\n",root);
}

void ask3()
{
    double root1=bisection(function2,-5,5,1e-5);
    double root2=newton(function2,function2Derivative,-5.0,1e-5);
    printf("roots %lf %lf \n",root1,root2);
}


double bisectionNew(function<double(double)> f,
                 double a, double b,
                 double tol = 1e-8,
                 int maxiter = 1000)
{
    double fa = f(a);
    double fb = f(b);

    if (fa == 0.0) return a;
    if (fb == 0.0) return b;

    if (fa * fb > 0.0)
        return -1.0;

    for (int i = 0; i < maxiter; i++)
    {
        double c = a + 3.0*(b - a) / 4.0;
        double fc = f(c);

        if (fabs(fc) < tol ||
            (b - a) / 2.0 < tol)
            return c;

        if ((fa < 0 && fc > 0) ||
            (fa > 0 && fc < 0))
        {
            b = c;
            fb = fc;
        }
        else
        {
            a = c;
            fa = fc;
        }
    }

    return a + (b - a) / 2.0;
}


void ask4()
{
    double root1 = bisectionNew(function1,1.0,10.0,1e-5);
    printf("Root1 = %lf\n",root1);
    double root2=bisectionNew(function2,-5,5,1e-5);
    printf("Root2 = %lf\n",root2);


}

double finite(function<double(double)> f,double x)
{
    const double eps=1e-5;
    return (f(x+eps)-f(x))/eps;
}

void ask5()
{
    const double a=-10.0;
    const double b= 10.0;
    const int points = 1000;
    int i;
    FILE *fp=fopen("function.txt","w");
    for(i=0;i<points;i++)
    {
        double x = a+i*1.0*(b-a)/(points-1.0);
        double realDer = function2Derivative(x);
        double estDer = finite(function2,x);
        fprintf(fp,"%lf %lf %lf\n",x,realDer,estDer);
    }
    fclose(fp);
}

int main()
{
    ask1();
    ask2();
    ask3();
    ask4();
    ask5();
    return 0;
}
