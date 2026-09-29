#include "rbf.h"
# include <math.h>
Rbf::Rbf()
{
    nweights=1;
    pattern_dimension=1;
    trainSet=NULL;
    testSet=NULL;
    init_arrays();
}

void    Rbf::init_arrays()
{
    int i,j;
    centroid.resize(nweights);
    variance.resize(nweights);
    weight.resize(nweights);
    for(i=0;i<nweights;i++)
    {
        centroid[i].resize(pattern_dimension);
        for(j=0;j<pattern_dimension;j++)
            centroid[i][j]=0.0;
        variance[i]=0.0;
        weight[i]=2.0 * (rand()*1.0/RAND_MAX-1.0);
    }
}

void    Rbf::setNumberOfWeights(int K)
{
    if(K>0)    nweights=K;
    init_arrays();
}

int     Rbf::getNumberOfWeights()
{
    return nweights;
}

void    Rbf::setTrainSet(Dataset *t)
{
    int i;
    trainSet=t;
    pattern_dimension=t->dimension();
    init_arrays();
    for(i=0;i<trainSet->count();i++)
    {
        double y=trainSet->getYPoint(i);
        bool found=false;
        for(int j=0;j<classVector.size();j++)
        {
            if(fabs(classVector[j]-y)<1e-5)
            {
                found=true;
                break;
            }
        }
        if(!found)
            classVector.push_back(y);
    }
}

void    Rbf::setTestSet(Dataset *t)
{
    if(trainSet==NULL) return;
    if(t->dimension()==trainSet->dimension()) testSet=t;
}

double  distance(Data &x, Data &y)
{
    double s=0.0;
    int i;
    for(i=0;i<x.size();i++)
        s+=pow(x[i]-y[i],2.0);
    return sqrt(s);
}

double  Rbf::gauss_function(Data &pattern,Data &center,double sigma)
{
    double p=distance(pattern,center);
    return exp(-p*p/(sigma * sigma));
}

Matrix  Rbf::matrix_transpose(Matrix &x)
{
    Matrix xx;
    xx.resize(x[0].size());
    int i,j;
    for(i=0;i<xx.size();i++)
    {
        xx[i].resize(x.size());
        for(j=0;j<x.size();j++)
        {
            xx[i][j]=x[j][i];
        }
    }
    return xx;
}

Matrix  Rbf::matrix_mult(Matrix &x,Matrix &y)
{
    int m=x.size();
    int p=x[0].size();
    int n=y[0].size();
    if(p!=y.size())
    {
        printf("Impossible to multiple \n");

    }
    else
    {
        Matrix z;
        z.resize(m);
        int i,j,k;
        for(i=0;i<m;i++) z[i].resize(n);
        for(i=0;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                z[i][j]=0.0;
                for(k=0;k<p;k++)
                {
                    z[i][j]=z[i][j]+x[i][k]*y[k][j];
                }
            }
        }
        return z;
    }
}

Matrix  Rbf::matrix_inverse(Matrix x)
{
    Matrix c=x;
    int npivot;
    double det;
    int pass, row, col, maxrow, i, j, error_flag;
    double temp, pivot, mult;
    int n=x.size();
     for(i=0; i<n; ++i) {
        for(j=0; j<n; ++j) {
            if(i==j) {
            c[i][j] = 1.0;
            } else {
            c[i][j] = 0.0;
              }
        }
       }

       det=1.0;
       npivot=0;


       for(pass=0; pass<n; ++pass) {
        maxrow=pass;
        for(row=pass; row<n; ++row)
            if(fabs(x[row][pass]) > fabs(x[maxrow][pass]))
            maxrow=row;

        if(maxrow != pass)
            ++npivot;

        for(col=0; col<n; ++col) {
            temp=x[pass][col];
            x[pass][col] = x[maxrow][col];
            x[maxrow][col] = temp;
            temp = c[pass][col];
            c[pass][col] = c[maxrow][col];
            c[maxrow][col] = temp;
        }


        pivot = x[pass][pass];
        det *= pivot;

        if(fabs(det) < 1.0e-40) {
            printf("Matrix is singular\n");
            return c;
        }


        for(col=0; col<n; ++col) {
            x[pass][col] = x[pass][col]/pivot;
            c[pass][col] = c[pass][col]/pivot;
        }

        for(row=0; row<n; ++row) {
            if(row != pass) {
                mult = x[row][pass];
                for(col=0; col<n; ++col) {
                    x[row][col] = x[row][col] - x[pass][col] * mult;
                    c[row][col] = c[row][col] - c[pass][col] * mult;
                }
            }
        }

       }

       if(npivot % 2 != 0)
        det = det * (-1.0);
      return c;
}

Matrix  Rbf::matrix_pseudoinverse(Matrix &a)
{
    Matrix b=matrix_transpose(a);
    Matrix e=matrix_mult(b,a);
    Matrix d=matrix_inverse(e);
    Matrix c=matrix_mult(d,b);
    return c;
}

void    Rbf::train()
{
    //phase1
    kmeans alg(trainSet,nweights);
    alg.runAlgorithm();
    centroid=alg.getCenters();
    variance=alg.getVariances();

    //phase2
    Matrix A,RealOutput;
    A.resize(trainSet->count());
    RealOutput.resize(trainSet->count());
    int i,j;
    for(i=0;i<A.size();i++)
    {
        RealOutput[i].push_back(trainSet->getYPoint(i));
        Data x=trainSet->getXPoint(i);
        A[i].resize(centroid.size());
        for(j=0;j<centroid.size();j++)
        {
          A[i][j]=gauss_function(x,centroid[j],variance[j]);

        }
    }
    Matrix pA=matrix_pseudoinverse(A);
    Matrix pW=matrix_mult(pA,RealOutput);
    for(i=0;i<pW.size();i++)
        weight[i]=pW[i][0];
}

double  Rbf::getOutput(Data &pattern)
{
    Data px;
    int j;
    for(j=0;j<centroid.size();j++)
      px.push_back(gauss_function(pattern,centroid[j],variance[j]));
    return product(weight,px);
}

double  Rbf::getClass(Data &pattern)
{
    double f=getOutput(pattern);
    int minClass=0;
    double minDist=fabs(classVector[0]-f);
    int i;
    for(i=0;i<classVector.size();i++)
    {
        double dist=fabs(classVector[i]-f);
        if(dist<minDist)
        {
            minClass=i;
            minDist=dist;
        }
    }
    return classVector[minClass];
}

double  Rbf::getTrainError()
{
    if(trainSet==NULL) return -1.0;
    double sum=0.0;
    int i;
    for(i=0;i<trainSet->count();i++)
    {
        Data x=trainSet->getXPoint(i);
        sum+=pow(getOutput(x)-trainSet->getYPoint(i),2.0);
    }
    return sum;
}

double  Rbf::product(Data &x, Data &y)
{
    int i;
    double sum=0.0;
    for(i=0;i<x.size();i++)
        sum+=x[i]*y[i];
    return sum;
}

double  Rbf::getTestError()
{
    if(testSet==NULL) return -1.0;
    double sum=0.0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data x=testSet->getXPoint(i);
        sum+=pow(getOutput(x)-testSet->getYPoint(i),2.0);
    }
    return sum;
}

double  Rbf::getClassError()
{
    if(testSet==NULL) return -1.0;
    int missed=0;
    int i;
    for(i=0;i<testSet->count();i++)
    {
        Data pattern=testSet->getXPoint(i);

        double d=getClass(pattern);
        double y=testSet->getYPoint(i);
        if(fabs(d-y)>1e-5) missed++;
    }
    return missed * 100.0/testSet->count();
}

