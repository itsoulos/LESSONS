#include <iostream>
# include <vector>
# include <string>
# include <math.h>
using namespace std;

typedef vector<int> IDATA;

void convertIntegerPart(int N,IDATA &result)
{
    while(N!=0)
    {
       int bit = N % 2;
       result.push_back(bit);
       N = N/2;
    }
}

void    convertDecimalPart(double d,IDATA &result)
{
    const int maxdigits=10;
    int digits=0;
    while(d>0 && digits<=maxdigits)
    {
        int f = (int)(2 * d);
        d = 2 * d-f;
        result.push_back(f);
        digits++;
    }
}

void    reverse(IDATA &x)
{
    unsigned int i;
    for(i=0;i<x.size()/2;i++)
    {
        int t = x[i];
        x[i]=x[x.size()-i-1];
        x[x.size()-i-1]=t;
    }
}

void    printData(IDATA &x)
{
    unsigned int i;
    for(i=0;i<x.size();i++)
        cout<<x[i]<<" ";

}

int main()
{
    double x=12.9429;
    double fl=floor(x);
    double decimal = x - fl;
    cout<<"decimal = "<<decimal<<endl;
    IDATA binaryIntPart,binaryDecimalPart;
    convertIntegerPart((int)fl,binaryIntPart);
    reverse(binaryIntPart);
    convertDecimalPart(decimal,binaryDecimalPart);
    printData(binaryIntPart);
    cout<<".";
    printData(binaryDecimalPart);
    return 0;
}
