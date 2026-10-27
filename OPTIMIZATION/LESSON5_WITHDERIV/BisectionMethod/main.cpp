# include <stdio.h>
# include <math.h>

double f(double x)
{
    return x*(x-3)*(x-3)+2;
}

double fp(double x)
{
    return (x-3)*(x-3)+2*(x-3)*x;
}

void bisectionMethod(double &a,double &b)
{
    int k=0;
    if(fp(a)>0 || fp(b)<0) return;
    while(true)
    {
        double c= a+(b-a)/2.0;
        if(fp(c)>0)
        {
            b=c;
        }
        else
        {
            a=c;
        }
        k++;
        printf("Iteration: %4d Interval:[%20.10lg %20.10lg]\n",
               k,a,b);
        if(fabs(b-a)<1e-6) break;
    }
}
int main()
{
    double a= 1;
    double b= 10;
    bisectionMethod(a,b);
    return 0;
}
