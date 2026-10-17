#include <vector>
#include <algorithm>
# include <stdio.h>
using namespace std;

void ask11()
{
    printf("===ASKSISI 1.1====\n");
    const int len =10;
    double x[len]={10.1,8.2,3.9,4.5,6.7,-1.2,4.3,10,12,14};
    int i;
    double sum=0.0;
    double avg=0.0;
    for(i=0;i<len;i++)
    {
        sum+=x[i];
    }
    avg=sum/len;
    printf("Sum=%lf Avg=%lf\n",sum,avg);
}
void ask12()
{
    printf("===ASKSISI 1.2====\n");
    const int len =10;
    int x[len]={-2,4,3,5,8,9,21,12,11,19};
    int i;
    int min=x[0];
    int max=x[0];
    int imin=0;
    int imax=0;
    for(i=0;i<len;i++)
    {
        if(x[i]<min)
        {
            min = x[i];
            imin = i;
        }
        if(x[i]>max)
        {
            max=x[i];
            imax=i;
        }
    }
    printf("Min pos %d Minimum %d \n",imin,min);
    printf("Max pos %d Max %d \n",imax,max);
}

void ask13()
{
    printf("===ASKSISI 1.3====\n");
    int a[6]={3,7,2,7,5,7};
    int x=7;
    int count=0;
    int i;
    for(i=0;i<6;i++)
    {
        if(a[i]==x)
        {
            printf("found at %d \n",i);
            count++;
        }
    }
    printf("Total found %d \n",count);
}

void ask14()
{
   printf("===ASKSISI 1.4====\n");
    const int len=10;
   int x[len]={-2,4,3,5,8,9,21,12,11,19};
   int i;
   for(i=0;i<len/2;i++)
   {
       int t=x[i];
       x[i]=x[len-i-1];
       x[len-i-1]=t;
   }
   for(i=0;i<len;i++)
       printf("%d  ",x[i]);
   printf("\n");
}

void ask15()
{
    printf("===ASKSISI 1.5====\n");
    const int len =10;
    double x[len]={0.0,-8.2,3.9,4.5,6.7,-1.2,4.3,10,12,14};
    int i;
    int countPos=0;
    int countNeg=0;
    int countZero=0;
    for(i=0;i<len;i++)
    {
        if(x[i]>0) countPos++;
        if(x[i]<0) countNeg++;
        if(x[i]==0.0) countZero++;
    }
    printf("Zero: %d Positive: %d Negative: %d\n",countZero,countPos,countNeg);
}
void pinakes()
{
    ask11();
    ask12();
    ask13();
    ask14();
    ask15();
}

void ask21()
{
    printf("===ASKSISI 2.1====\n");

    vector<int> x;
    x.resize(5);
    x[0]=1;x[1]=2;x[2]=4;x[3]=10;x[4]=29;
    int i;
    for(i=0;i<x.size();i++)
        printf("x = %d \n",x[i]);
}

void ask22()
{
    printf("===ASKSISI 2.2====\n");

    vector<int> x;

    x.push_back(1);
    x.push_back(2);
    x.push_back(4);
    x.push_back(10);
    x.push_back(29);
    int i;
    for(i=0;i<x.size();i++)
        printf("x = %d \n",x[i]);
}

void ask23()
{
    printf("===ASKSISI 2.3====\n");

    vector<int> x;

    x.push_back(19);
    x.push_back(2);
    x.push_back(44);
    x.push_back(10);
    x.push_back(29);
    int i;
    vector<int> y = x;
    sort(x.begin(), x.end());
    for(i=0;i<x.size();i++)
        printf(" %d ",x[i]);
    printf("\n");
    sort(y.begin(), y.end(), greater<int>());
    for(i=0;i<y.size();i++)
        printf(" %d ",y[i]);
    printf("\n");
}

void ask24()
{
    printf("===ASKSISI 2.4====\n");

    vector<int> x;

    x.push_back(19);
    x.push_back(2);
    x.push_back(44);
    x.push_back(10);
    x.push_back(29);
    auto min_it = min_element(x.begin(), x.end());
    auto max_it = max_element(x.begin(), x.end());
    printf("Min %d Max %d\n",*min_it,*max_it);
}

void ask25()
{

    printf("===ASKSISI 2.5====\n");

    vector<int> x;

    x.push_back(19);
    x.push_back(2);
    x.push_back(19);
    x.push_back(10);
    x.push_back(29);
    int n = count(x.begin(), x.end(), 19);
    printf("found %d times \n",n);
}

void ask26()
{
    printf("===ASKSISI 2.5====\n");

    vector<int> x;

    x.push_back(21);
    x.push_back(19);
    x.push_back(19);
    x.push_back(10);
    x.push_back(29);
    auto it = find(x.begin(), x.end(), 19);

    if (it != x.end())
    {
        printf("found %d at position %d \n",*it,it-x.begin());
    }
    else
    {
        printf("not found \n");
    }
}
void stl()
{
    ask21();
    ask22();
    ask23();
    ask24();
    ask25();
    ask26();
}


int main()
{
    pinakes();
    stl();
    return 0;
}
