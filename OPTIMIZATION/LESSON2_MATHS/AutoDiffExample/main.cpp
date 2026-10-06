#include <iostream>
#include <autodiff/forward/dual.hpp>
#include <chrono>
#include <iostream>
using namespace std::chrono;
using namespace std;
using namespace autodiff;
dual f(const dual &x,const dual &y,const dual &z)
{
 return (x+y+z)*exp(x*y+z);
}

//os pros x
double f1(double x,double y, double z)
{
    return exp(x*y+z)+(x+y+z)*y*exp(x*y+z);
}

//os pros y
double f2(double x,double y,double z)
{
    return exp(x*y+z)+(x+y+z)*x*exp(x*y+z);
}

//os pros z
double f3(double x,double y,double z)
{
    return exp(x*y+z)+(x+y+z)*exp(x*y+z);
}
int main()
{
    auto start1 = high_resolution_clock::now();
    for(int i=0;i<1000;i++)
    {
    dual x = 1.0; dual y = 2.0;
    dual z = 3.0; dual u = f(x, y, z);
    double dudx = derivative(f, wrt(x), at(x, y, z));
    double dudy = derivative(f, wrt(y), at(x, y, z));
    double dudz = derivative(f, wrt(z), at(x, y, z));
    if(i==0)
    cout<<"Derivatives "<<dudx<<" "<<dudy<<" "<<dudz<<endl;
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    cout<<"Autodiff time was "<<duration1.count()<<endl;

    auto start2 = high_resolution_clock::now();
    for(int j=0;j<1000;j++)
    {
        double x=1.0,y=2.0,z=3.0;
        double d1=f1(x,y,z);
        double d2=f2(x,y,z);
        double d3=f3(x,y,z);
        if(j==0)
        cout<<"Derivatives "<<d1<<" "<<d2<<" "<<d3<<endl;
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    cout<<"Real derivative time was "<<duration2.count()<<endl;
    return 0;
}
