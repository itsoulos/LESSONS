# include <stdio.h>
# include <math.h>
# include <vector>
using namespace std;
typedef vector<double> Data;
typedef vector<Data> Matrix;

double f(double x)
{
    return x*sin(x);
}

double fp(double x)
{
    return sin(x)+x*cos(x);
}


void    Gauss(Matrix &mat,Data &x)
{
    unsigned int n = mat.size();
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(abs(mat[i][i]) < abs(mat[j][i]))
            {
                for(int k=0;k<n+1;k++)
                {
                    /* swapping mat[i][k] and mat[j][k] */
                    mat[i][k]=mat[i][k]+mat[j][k];
                    mat[j][k]=mat[i][k]-mat[j][k];
                    mat[i][k]=mat[i][k]-mat[j][k];
                }
            }
      }
    }
    /* performing Gaussian elimination */
   for(int i=0;i<n-1;i++)
   {
       for(int j=i+1;j<n;j++)
       {
           float f=mat[j][i]/mat[i][i];
           for(int k=0;k<n+1;k++)
           {
             mat[j][k]=mat[j][k]-f*mat[i][k];
           }
       }
   }
   for(int i=n-1;i>=0;i--)
   {
       x[i]=mat[i][n];

       for(int j=i+1;j<n;j++)
       {
         if(i!=j)
         {
             x[i]=x[i]-mat[i][j]*x[j];
   }
 }
 x[i]=x[i]/mat[i][i];
   }
}

double poly(double a,double b,double x)
{

    //construct matrixes
    Matrix A;
    int n = 4;
    A.resize(n);
    for(int i=0;i<n;i++)
    {
        A[i].resize(n+1);
    }
    A[0][0]=pow(a,3);A[0][1]=a*a;A[0][2]=a;A[0][3]=1;A[0][4]=f(a);
    A[1][0]=pow(b,3);A[1][1]=b*b;A[1][2]=b;A[1][3]=1;A[1][4]=f(b);
    A[2][0]=3*a*a;A[2][1]=2*a;A[2][2]=1;A[2][3]=0;A[2][4]=fp(a);
    A[3][0]=3*b*b;A[3][1]=2*b;A[3][2]=1;A[3][3]=0;A[3][4]=fp(b);
    Data xsol;
    xsol.resize(n);
    Gauss(A,xsol);
    return xsol[0]*pow(x,3)+xsol[1]*pow(x,2)+xsol[2]*x+xsol[3];
}

void goldenSearchForPolynomial(double &a,double &b)
{
    double phi = (sqrt(5.0)-1.0)/2.0;
    int iteration = 1;
    while(true)
    {
        double x1 = a+(1-phi)*(b-a);
        double x2 = a+phi * (b-a);
        double diff =fabs(x1-x2);
        if(diff<1e-6) break;
        if(poly(a,b,x1)<poly(a,b,x2))
        {
            b = x2;
        }
        else
        {
            a=x1;
        }
        iteration++;

    }
}

void testPolynomial(double a,double b)
{
    const int points=100;
    double dx=(b-a)/points;
    for(double x=a;x<=b;x+=dx)
    {
        double f1=f(x);
        double f2=poly(a,b,x);
        printf("%lf %lf %lf \n",x,f1,f2);
    }
}

void DavidonMethod(double &a,double &b)
{
    int k=0;
    if(fp(a)>0 || fp(b)<0) return;
    while(true)
    {
        double copyA = a;
        double copyB = b;
        goldenSearchForPolynomial(copyA,copyB);


        if(f(a)>f(copyA))
        {
            a = copyA;
        }
        else
        if(f(b)>f(copyA))
        {
            b = copyA;
        }
        k=k+1;
        printf("Search k=%4d a =%20.10lg b=%20.10lg\n",k,a,b);
        if(fabs(b-a)<1e-5) break;
    }
}
int main()
{
    double a=-1;
    double b=1;
    testPolynomial(a,b);
    DavidonMethod(a,b);
    return 0;
}
