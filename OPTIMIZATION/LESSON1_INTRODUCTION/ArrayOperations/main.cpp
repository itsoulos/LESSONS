#include <iostream>
# include <vector>
# include <string>
# include <math.h>
using namespace std;

typedef vector<double> Data;
typedef vector<Data> Matrix;

int rows(Matrix &m)
{
    return m.size();
}

int columns(Matrix &m)
{
    return m[0].size();
}

Matrix makeMatrix(int m,int n)
{
    Matrix X;
    X.resize(m);
    for(int i=0;i<m;i++)
        X[i].resize(n);
    return X;
}

Matrix addMatrix(Matrix &A,Matrix &B)
{
    Matrix C = makeMatrix(rows(A),columns(A));
    for(int i=0;i<rows(A);i++)
    {
        for(int j=0;j<columns(A);j++)
        {
            C[i][j]=A[i][j]+B[i][j];
        }
    }
    return C;
}

Matrix multipleBy(double lambda,Matrix &m)
{

    Matrix x = makeMatrix(rows(m),columns(m));
    for(int i=0;i<rows(m);i++)
    {
        for(int j=0;j<columns(m);j++)
        {
            x[i][j] = lambda * m[i][j];
        }
    }
    return x;
}

Matrix multMatrix(Matrix &A,Matrix &B)
{
    Matrix C = makeMatrix(rows(A),columns(B));
    for(int i=0;i<rows(C);i++)
    {
        for(int j=0;j<columns(C);j++)
        {
            double sum = 0.0;
            for(int k=0;k<rows(A);k++)
            {
                sum = sum + A[i][k]*B[k][j];
            }
            C[i][j]=sum;
        }
    }
    return C;
}

Matrix subMatrix(Matrix &m,int removeRow,int removeColumn)
{
   Matrix x = makeMatrix(rows(m)-1,columns(m)-1);
   int icount=0,jcount = 0;
   for(int i=0;i<rows(m);i++)
   {
       if(i==removeRow) continue;
       jcount=0;
       for(int j=0;j<columns(m);j++)
       {
           if(j==removeColumn) continue;
           x[icount][jcount]=m[i][j];
           jcount++;
       }
       icount++;
   }
   return x;
}

double det(Matrix &m)
{
    if(rows(m)!=columns(m)) return -1;
    if(rows(m)==2)
    {
        return m[0][0]*m[1][1]-m[1][0]*m[0][1];
    }
    double sum = 0.0;
    int sign = 1;
    for(int i=0;i<columns(m);i++)
    {
        Matrix x = subMatrix(m,0,i);
        sum = sum + sign *det(x);
        sign = -sign;
    }
    return sum;
}


void    readMatrix(Matrix &m)
{
    for(int i=0;i<rows(m);i++)
    {
        for(int j=0;j<columns(m);j++)
        {
            cout<<"Enter element at "<<" "<<i<<" "<<j<<endl;
            cin>>m[i][j];
        }
    }
}
void    printMatrix(Matrix &m)
{
    for(int i=0;i<rows(m);i++)
    {
        for(int j=0;j<columns(m);j++)
        {
            cout<<m[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    float x;
    double y;
    long double z;

    Matrix A = makeMatrix(3,3);
    Matrix B = makeMatrix(3,3);
    readMatrix(A);
    readMatrix(B);
    Matrix C = multMatrix(A,B);
    printMatrix(C);
    cout<<"Dets "<<det(A)<<"..."<<det(B)<<"..."<<det(C)<<endl;
    return 0;
}
