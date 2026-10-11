#include <stdio.h>
# include <stdlib.h>
# include <math.h>

double f(double x)
{
    return x*(x-3)*(x-3)+2;
}
double fib(int k)
{
    return (pow(1+sqrt(5),k+1)-pow(1-sqrt(5),k+1))/(pow(2.0,k+1)*sqrt(5));
}
void fibSearch(double &a,double &b)
{

    int iteration = 2;
    while(true)
    {
        double fk= fib(iteration);
        double fk1=fib(iteration+1);
        printf("ratio %lf\n",fk/fk1);
         double phi = fk/fk1;//(sqrt(5.0)-1.0)/2.0;
        double x1 = a+(1-phi)*(b-a);
        double x2 = a+phi * (b-a);
        double diff =fabs(x1-x2);
        if(diff<1e-6) break;
        if(f(x1)<f(x2))
        {
            b = x2;
        }
        else
        {
            a=x1;
        }
        iteration++;
        printf("Iteration=%4d Range=[%10.5lg,%10.5lg]\n",
               iteration,a,b);
    }
}
int main()
{
    double a = 0;
    double b = 10;
    fibSearch(a,b);
    printf("On termination range=[%10.5lg,%10.5lg]\n",a,b);
    return 0;
}
