# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <vector>
using namespace std;

typedef vector<double> Data;
typedef vector<Data>   Matrix;

//epistrofi grammon
int  rows(Matrix &a)
{
    return a.size();
}

//epistrofi stilon
int cols(Matrix &a)
{
    return a[0].size();
}

//prosthesi pinakon an auto epitrepetai
Matrix addMatrix(Matrix &a,Matrix &b)
{
    if(rows(a)!=rows(b) || cols(a)!=cols(b)) return a;
    Matrix c=a;
    int i,j;
    for(i=0;i<rows(a);i++)
    {
        for(j=0;j<cols(a);j++)
        {
            c[i][j]+=b[i][j];
        }
    }
    return c;
}

//pollaplasiamos arithmou me pinaka
Matrix multArray(double value,Matrix &a)
{
    Matrix b=a;
    int i,j;
    for(i=0;i<rows(a);i++)
    {
        for(j=0;j<cols(a);j++)
        {
            b[i][j]*=value;
        }
    }
    return b;
}

//ypologismos anastrofou pinaka
Matrix transposeArray(Matrix &a)
{
    int i,j;
    Matrix b;
    b.resize(cols(a));
    for(i=0;i<rows(b);i++)
    {
        b[i].resize(rows(a));
        for(j=0;j<cols(b);j++)
            b[i][j]=a[j][i];
    }
    return b;
}

//ektyposi tou pinaka
void    printMatrix(Matrix &a)
{
    int i,j;
    for(i=0;i<rows(a);i++)
    {
        for(j=0;j<cols(a);j++)
        {
            printf("%6.2lf ",a[i][j]);
        }
        printf("\n");
    }
}

//dimiourgia tyxaiou pinaka MxN
Matrix randomMatrix(int M,int N)
{
    Matrix a;
    int i,j;
    a.resize(M);
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
            a[i].push_back(100.0 * rand()*1.0/RAND_MAX);
    }
    return a;
}

int main(int argc, char *argv[])
{
    Matrix a,b;
    a=randomMatrix(5,5);
    b=randomMatrix(5,5);
    printMatrix(a);
    printf("===============\n");
    Matrix c=addMatrix(a,b);
    printMatrix(b);
    printf("===============\n");
    printMatrix(c);
   return 0;

}
