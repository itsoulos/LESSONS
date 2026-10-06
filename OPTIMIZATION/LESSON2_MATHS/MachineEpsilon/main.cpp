# include <stdio.h>

void printFloatEpsilon()
{
    float epsilon = 1.0;
    int it = 0;
    const int maxit=300;
    float num = 1.0;
    float beta =0.0;
    while(it<=maxit)
    {
        epsilon = epsilon /2.0;
        beta = num+epsilon;
        if(beta==num) break;
        it++;
    }
    printf("Float statistics: %.20g %.20g \n",beta,epsilon);
}

void    printDoubleEpsilon()
{
    double epsilon = 1.0;
    int it = 0;
    const int maxit=300;
    double num = 1.0;
    double beta =0.0;
    while(it<=maxit)
    {
        epsilon = epsilon /5.0;
        beta = num+epsilon;
        if(beta==num) break;
        it++;
    }
    printf("Double statistics: %.20lg %.20lg \n",beta,epsilon);
}

void    printLongDoubleEpsilon()
{
    long double epsilon = 1.0;
    int it = 0;
    const int maxit=300;
    long double num = 1.0;
    long double beta =0.0;
    while(it<=maxit)
    {
        epsilon = epsilon /2.0;
        beta = num+epsilon;
        if(beta==num) break;
        it++;
    }
    printf("Long Double statistics: %.50Lg %.50Lg \n",beta,epsilon);
}
int main()
{
    printFloatEpsilon();
    printDoubleEpsilon();
    printLongDoubleEpsilon();
    return 0;
}
