# include <math.h>
# include <stdio.h>

int fcount = 0;
double f(double x)
{
	fcount++;
       return (x-3)*(x-5);
}

double getRoot(double a,double b,int &status)
{
    double x= (a+b)/2;
    const int imax=200;
    int it = 0;
    while(it<imax)
    {

        if(fabs(f(x))<1e-8) {
            status =1;
            return x;
        }
        else if (f(a)*f(x)<0)
        {
            b =x;
            x = (a+b)/2;
        }
        else
        {
            a=x;
            x=(a+b)/2;
        }
        printf("Iters=%4d X=%20.10lf F(x)=%20.10lf\n",it,x,f(x));
        it++;
    }
    status=0;
    return -1;
}

int main()
{
    double a= 4;
    double b=  10;
    int status =1;
    double x = getRoot(a,b,status);
    if(status!=0)
        printf("Root: %20.10lg\n",x);
    else printf("No root found\n");
    printf("Function calls = %d\n",fcount);
    return 0;
}
