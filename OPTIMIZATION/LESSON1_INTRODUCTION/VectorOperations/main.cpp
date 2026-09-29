#include <iostream>
# include <vector>
# include <string>
# include <math.h>
using namespace std;


typedef vector<double> Data;

Data addVectors(Data &x,Data &y)
{
    if(x.size()!=y.size())
        cout<<"Lathos";
    Data z;
    z.resize(x.size());
    unsigned int i;
    for(i=0;i<x.size();i++)
        z[i]=x[i]+y[i];
    return z;
}

double productVectors(Data &x,Data &y)
{
    double s = 0.0;
    unsigned int i;
    for(i=0;i<x.size();i++)
        s+=x[i]*y[i];
    return s;
}

double norm1(Data &x)
{
    //l1 norm
    double s = 0.0;
    unsigned int i;
    for(i=0;i<x.size();i++)
        s+=fabs(x[i]);
    return s;
}

double norm2(Data &x)
{
    //l2 norm
    double s = 0.0;
    unsigned int i;
    for(i=0;i<x.size();i++)
        s+=x[i]*x[i];
    return sqrt(s);
}

double normInf(Data &x)
{
    //infinity norm
    double s = 0.0;
    unsigned int i;
    s = fabs(x[0]);
    for(i=0;i<x.size();i++)
    {
        if(fabs(x[i])>s)
            s= fabs(x[i]);
    }
    return s;
}

Data readVector(int size)
{
    int i;
    Data x;
    x.resize(size);
    for(i=0;i<size;i++)
    {
        cout<<"enter element ";
        cin>>x[i];
    }
    return x;
}

void printVector(const Data &x)
{
    unsigned int i;
    cout<<"[";
    for(i=0;i<x.size();i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<"]"<<endl;
}

int main()
{
    Data x,y,z;
    x = readVector(5);
    y = readVector(5);
    z = addVectors(x,y);
    double p = productVectors(x,y);
    double l1 = norm1(x);
    double l2 = norm2(x);
    double linf = normInf(x);
    printVector(z);
    cout<<"product "<<p<<endl;
    cout<<"norms "<<l1<<" "<<l2<<" "<<linf<<endl;
    return 0;
}
