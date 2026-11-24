#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Data;
typedef vector<Data> Matrix;

class Problem
{
protected:
    int dimension;
    Data left, right;
    Data bestx;
    double besty;
    int functionCalls;
public:
    Problem(int n);
    int getDimension() const;
    Data getSample();
    void setLeftMargin(Data &x);
    void setRightMargin(Data &x);
    Data getLeftMargin() const;
    Data getRightMargin() const;
    virtual double funmin(Data &x) = 0;
    virtual Data gradient(Data &x) = 0;
    /**
     * @brief statFunmin Kalei prota tin funmin(x)
     * kai diatirei to bestvalue kai kanei update
     * ta function calls
     * @param x
     */
    double statFunmin(Data &x);
    double grms(Data &x);
    Data    getBestx() const;
    double  getBesty() const;
    int     getFunctionCalls() const;
    double  getVolume() const;
    ~Problem();
};

Problem::Problem(int n)
{
    dimension = n;
    left.resize(dimension);
    right.resize(dimension);
    besty = 1e+100;
    functionCalls = 0;
}

double  Problem::getVolume() const
{
    double s = 1.0;
    for(int i=0;i<dimension;i++)
        s*=(right[i]-left[i]);
    return s;
}

double    Problem::statFunmin(Data &x)
{
    double y = funmin(x);
    if(y<besty)
    {
        besty = y;
        bestx = x;
    }
    ++functionCalls;
    return y;
}

Data    Problem::getBestx() const
{
    return bestx;
}

double  Problem::getBesty() const
{
    return besty;
}

int     Problem::getFunctionCalls() const
{
    return functionCalls;
}

int Problem::getDimension() const
{
    return dimension;
}

Data Problem::getSample()
{
    Data x;
    x.resize(dimension);
    double r;
    for (int i = 0; i < dimension; i++)
    {
        r = ((double)rand()/(double)RAND_MAX);
        if (r < 0)
            r = -r;
        x[i] = left[i] + (right[i] - left[i]) * r;
    }
    return x;
}
void Problem::setLeftMargin(Data &x)
{
    left = x;
}

void Problem::setRightMargin(Data &x)
{
    right = x;
}
Data Problem::getLeftMargin() const
{
    return left;
}

Data Problem::getRightMargin() const
{
    return right;
}

double Problem::grms(Data &x)
{
    Data g = gradient(x);
    int i;
    double s = 0.0;
    for (i = 0; i < x.size(); i++)
        s = s + g[i] * g[i];
    return sqrt(s / x.size());
}

Problem::~Problem()
{
}

class RastriginProblem : public Problem
{
public:
    RastriginProblem();
    double funmin(Data &x);
    Data gradient(Data &x);
};

RastriginProblem::RastriginProblem()
    : Problem(2)
{
    Data l, r;
    l.resize(2);
    r.resize(2);
    for (int i = 0; i < 2; i++)
    {
        l[i] = -1.0;
        r[i] = 1.0;
    }
    setLeftMargin(l);
    setRightMargin(r);
}

double RastriginProblem::funmin(Data &x)
{
    return x[0] * x[0] + x[1] * x[1] - cos(18.0 * x[0]) - cos(18.0 * x[1]);
}

Data RastriginProblem::gradient(Data &x)
{
    Data g;
    g.resize(2);
    g[0] = 2.0 * x[0] + 18.0 * sin(18.0 * x[0]);
    g[1] = 2.0 * x[1] + 18.0 * sin(18.0 * x[1]);
    return g;
}

class Test2nProblem : public Problem
{
public:
    Test2nProblem(int n);
    double funmin(Data &x);
    Data gradient(Data &x);
};

Test2nProblem::Test2nProblem(int n)
    :Problem(n)
{
    Data l, r;
    l.resize(n);
    r.resize(n);
    for (int i = 0; i < n; i++)
    {
        l[i] = -5.0;
        r[i] = 5.0;
    }
    setLeftMargin(l);
    setRightMargin(r);
}

double Test2nProblem::funmin(Data &x)
{
    double sum=0.0;
    for(int i=0;i<dimension;i++)
      sum+=0.5 * (pow(x[i],4.0)-16.0 * pow(x[i],2.0)+5.0*x[i]);
   return sum;
}

Data Test2nProblem::gradient(Data &x)
{
    Data g;
    g.resize(dimension);
    for(int i=0;i<dimension;i++)
        {
            g[i]=0.5 * (4.0*pow(x[i],3.0)-32*x[i]+5.0);
        }
    return g;
}

class GradientDescent
{
protected:
    double rate;
    Data xpoint;
    double ypoint;
    Problem *myProblem;
public:
    GradientDescent(Problem *p);
    void setRate(double r);
    double getRate() const;
    virtual void    updateRate();
    virtual void    updatePoint();
    void    setPoint(Data &x,double y);
    void    Solve();
    Data    getBestx() const;
    double  getBesty() const;
    ~GradientDescent();
};

GradientDescent::GradientDescent(Problem *p)
{
    myProblem = p;
    rate = 0.001;
    xpoint = myProblem->getSample();
    ypoint = myProblem->statFunmin(xpoint);
}

Data    GradientDescent::getBestx() const
{
    return xpoint;
}

double  GradientDescent::getBesty() const
{
    return ypoint;
}

void    GradientDescent::setPoint(Data &x, double y)
{
    xpoint = x;
    ypoint = y;

}
void    GradientDescent::setRate(double r)
{
    if(r>0) rate = r;
}

double  GradientDescent::getRate() const
{
    return rate;
}

void    GradientDescent::updateRate()
{
    //nothing here
}

void    GradientDescent::updatePoint()
{
    Data g = myProblem->gradient(xpoint);
    unsigned int i;
    for(i=0;i<g.size();i++)
        xpoint[i]=xpoint[i]-rate * g[i];
    ypoint=myProblem->statFunmin(xpoint);
}

void    GradientDescent::Solve()
{
    int k=0;
    while(true)
    {
        updateRate();
        updatePoint();
        k=k+1;
        if(myProblem->grms(xpoint)<1e-3) break;
    }
}
GradientDescent::~GradientDescent()
{
    //nothing here
}



class GradientWithLS :public GradientDescent
{
public:
    GradientWithLS(Problem *p);
    double  fl(double h);
    void    goldenSearch(double &a,double &b);
    virtual void    updateRate();

};

GradientWithLS::GradientWithLS(Problem *p)
    :GradientDescent(p)
{

}

double  GradientWithLS::fl(double h)
{
    Data trialx = xpoint;
    unsigned int i;
    Data g = myProblem->gradient(xpoint);
    for(i=0;i<xpoint.size();i++)
    {
        trialx[i]=trialx[i]-h * g[i];
    }
    return myProblem->statFunmin(trialx);
}

void GradientWithLS::goldenSearch(double &a,double &b)
{
    double phi = (sqrt(5.0)-1.0)/2.0;
    int iteration = 1;
    while(true)
    {
        double x1 = a+(1-phi)*(b-a);
        double x2 = a+phi * (b-a);
        double diff =fabs(x1-x2);
        if(diff<1e-6) break;

        if(fl(x1)<fl(x2))
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

void    GradientWithLS::updateRate()
{
    double lambda = rate;
    double a = lambda * 0.9;
    double b = lambda * 1.1;
    goldenSearch(a,b);
    rate = a;
}

class Statistics
{
private:
    /**
     * @brief bestyValue o pinakas me tis kalyteres times apo tis ekteleseis
     */
    Data bestyValue;
    /**
     * @brief fcallsValue o pinakas me tis kliseis stin synartisi anamesa stis
     * ektelseis.
     */
    vector<int> fcallsValue;
public:
    /**
     * @brief Statistics i synartisi dimioyrgias
     */
    Statistics();
    /**
     * @brief addProblem prosthetei to problima ston pinaka statistikon
     * @param p
     */
    void addProblem(Problem *p);
    /**
     * @brief printStatistics ektyponei stin othoni tis metriseis
     */
    void printStatistics();
    ~Statistics();
};

Statistics::Statistics()
{
    bestyValue.resize(0);
    fcallsValue.resize(0);
}

void Statistics::addProblem(Problem *p)
{
    bestyValue.push_back(p->getBesty());
    fcallsValue.push_back(p->getFunctionCalls());
}

void Statistics::printStatistics()
{
    int n = (int)bestyValue.size();
    printf("Executions: %4d\n===================\n",n);
    int totalFcalls = 0;
    double miny = 1e+100;
    int timesMinimumFound = 0;
    for(int i=0;i<n;i++)
    {
        printf("RUN: %4d BEST VALUE: %20.10lg FUNCTION CALLS: %4d\n",
               i+1,bestyValue[i],fcallsValue[i]);
        totalFcalls+=fcallsValue[i];
        if(i==0 || bestyValue[i]<miny) miny=bestyValue[i];
    }
    for(int i=0;i<n;i++)
    {
        if(fabs(bestyValue[i]-miny)<1e-6)
            timesMinimumFound++;
    }
    printf("Average Function calls: %20.2lf\n",totalFcalls*1.0/n);
    printf("Minimum Function Value: %20.10lg\n",miny);
    printf("Percent Minimum  Found: %20.2lf%%\n",timesMinimumFound*100.0/n);
}

Statistics::~Statistics()
{
    //nothing here
}

class Collection
{
private:
    Matrix xdata;
    Data   ydata;
public:
    /**
     * @brief Collection Synartisi dimioyrgias
     */
    Collection();
    /**
     * @brief addPoint prosthetei ena neo simeio stin syllogi
     * @param x
     * @param y
     */
    void    addPoint(Data &x,double &y);
    /**
     * @brief getPoint Epistrefei ena simeio sto deigma
     * @param pos
     * @param x
     * @param y
     */
    void    getPoint(int pos,Data &x,double &y);
    /**
     * @brief haveGraphMinima Epistrefei alithes an exei graph minima mesa sto deigma
     * @param x
     * @param y
     * @param distance
     * @return
     */
    bool    haveGraphMinima(Data &x,double &y,double distance);
    /**
     * @brief resizeInFraction krataei ta fraction % kalytera simeia sto deigma
     * @param fraction
     */
    void    resizeInFraction(double fraction);
    /**
     * @brief getSize epistrefei to plithos ton simeion stin syllogi
     * @return
     */
    int     getSize() const;

    /**
     * @brief getDistance Eyklidia apostasi
     * @param x
     * @param y
     * @return
     */
    double  getDistance(Data &x,Data &y);

    /**
     * @brief isPointIn epistrefei alithes an ena deigma yparxei idi mesa
     * @param x
     * @param y
     * @return
     */
    bool isPointIn(Data &x,double  &y);

    void clear();
    /** Synartisi diagrafis
     */
    ~Collection();
};

Collection::Collection()
{
    xdata.resize(0);
    ydata.resize(0);
}

void Collection::clear()
{
    xdata.resize(0);
    ydata.resize(0);
}

double  Collection::getDistance(Data &x,Data &y)
{
    double sum = 0.0;
    for(int i=0;i<x.size();i++)
    {
        sum+=(x[i]-y[i])*(x[i]-y[i]);
    }
    return sqrt(sum/x.size());
}


void    Collection::resizeInFraction(double fraction)
{
    for(int i=0;i<ydata.size();i++)
    {
        for(int j=0;j<ydata.size()-1;j++)
        {
            if(ydata[j+1]<ydata[j])
            {
                double t = ydata[j];
                ydata[j]=ydata[j+1];
                ydata[j+1]=t;
                Data tx = xdata[j];
                xdata[j]=xdata[j+1];
                xdata[j+1]=tx;
            }
        }
    }
    int newSize = (int)(fraction * xdata.size());
    xdata.resize(newSize);
    ydata.resize(newSize);
}

bool    Collection::isPointIn(Data &x,double &y)
{
    for(int i=0;i<xdata.size();i++)
    {
        double d = getDistance(x,xdata[i]);
        if(d<1e-4) return true;
    }
    return false;
}

void    Collection::addPoint(Data &x,double &y)
{
    if(!isPointIn(x,y))
    {
        xdata.push_back(x);
        ydata.push_back(y);

    }
}

void    Collection::getPoint(int pos,Data &x,double &y)
{
    x=xdata[pos];
    y=ydata[pos];
}

bool    Collection::haveGraphMinima(Data &x,double &y,double distance)
{
    for(int i=0;i<ydata.size();i++)
    {
        if(ydata[i]<y && getDistance(x,xdata[i])<distance)
            return true;
    }
    return false;
}

int     Collection::getSize() const
{
    return xdata.size();
}

Collection::~Collection()
{
    //nothing here
}

class Mlsl
{
private:
    Problem *myProblem;
    int iter;
    int maxiters;
    int nsamples;
    Collection minima;
    Collection mx;
    Data bestx;
    double besty;
    double gammaFraction;
    double computeDistance();
    string terminationMethod="kan";//accepted values: maxiters,kan,doublebox
    //for kan criterion
    int wcount=0,tcount=0;
    //for doublebox criterion
    int oldminima;
    double x1=0.0,x2=0.0,stopat=0.0;
public:
    Mlsl(Problem *p);
    void    setTerminationMethod(string m);
    string  getTerminationMethod() const;
    void setMaxiters(int m);
    int  getMaxiters() const;
    void    setNsamples(int n);
    int     getNsamples() const;
    void    setGammaFraction(double g);
    double  getGammaFraction() const;
    Data    getBestx();
    double  getBesty();
    void    Solve();
    void    Step();
    bool    Terminated();
    ~Mlsl();
};


Mlsl::Mlsl(Problem *p)
{
    myProblem = p;
    maxiters = 100;
    nsamples = 100;
    gammaFraction =0.2;
}

void    Mlsl::setTerminationMethod(string m)
{
    terminationMethod = m;
}

string  Mlsl::getTerminationMethod() const
{
    return terminationMethod;
}

void    Mlsl::setNsamples(int n)
{
    if(n>0) nsamples = n;
}

int     Mlsl::getNsamples() const
{
    return nsamples;
}

void    Mlsl::setMaxiters(int m)
{
    if(m>0) maxiters = m;
}

int Mlsl::getMaxiters() const
{
    return maxiters;
}

void    Mlsl::setGammaFraction(double g)
{
    if(g>0 && g<1) gammaFraction = g;
}

double  Mlsl::getGammaFraction() const
{
    return gammaFraction;
}

Data    Mlsl::getBestx()
{
    return bestx;
}

double  Mlsl::getBesty()
{
    return besty;
}

double Mlsl::computeDistance()
{
    double s = 4.0;
    double ms =myProblem->getVolume();
    double gamma = tgamma(1.0+myProblem->getDimension()/2.0);
    double logk = log(iter*1.0)/iter;
    double xx  = s * ms * gamma * logk;
    return sqrt(M_PI)*pow(xx,myProblem->getDimension());
}

void    Mlsl::Step()
{
    mx.clear();
    //phase1
    for(int i=1;i<=nsamples;i++)
    {
        Data x =myProblem->getSample();
        double y = myProblem->statFunmin(x);
        mx.addPoint(x,y);
    }
    mx.resizeInFraction(gammaFraction);
    //phase2
    int n = mx.getSize();
    for(int i=0;i<n;i++)
    {
        Data x;
        double y;
        mx.getPoint(i,x,y);
        double rc =computeDistance();
        if(!mx.haveGraphMinima(x,y,rc))
        {
            tcount++;
            GradientWithLS gd(myProblem);
            gd.setPoint(x,y);
            gd.Solve();
            x=gd.getBestx();
            y=gd.getBesty();
            minima.addPoint(x,y);
            wcount = minima.getSize();
            if(y<besty)
            {
                besty=y;
                bestx=x;
            }
        }
    }
}
void    Mlsl::Solve()
{
    besty=1e+100;
    iter =1 ;
    wcount = 0;
    tcount = 0;
    x1=0.0;
    x2=0.0;
    oldminima=0;
    stopat=0.0;
    do
    {
        Step();
    }while(!Terminated());
}

bool    Mlsl::Terminated()
{
    iter++;

    if(terminationMethod == "maxiters")
    {
        printf("MLSL. ITERS: %4d BESTY: %20.10lg MINIMA: %4d\n",
               iter,besty,minima.getSize());
        return iter>=maxiters;
    }
    else
    if(terminationMethod=="kan")
    {
        double wtilde = wcount*(tcount-1.0)/(tcount-wcount-2.0);
        printf("KAN. ITERS: %4d WTILDE=%.2lf W=%4d\n",iter,wtilde,wcount);
        if(fabs(wtilde-wcount)<0.5) return true;
    }
    else
    if(terminationMethod=="doublebox")
    {
        int v = wcount-oldminima;
        x1+=v;
        x2+=(v*v);
        double variance = fabs((x1/iter)-(x2/iter)*(x2/iter));
        variance = sqrt(variance);
        if(oldminima!=wcount)
        {
            stopat = variance/2.0;
            oldminima = wcount;
        }
        printf("DOUBLEBOX. ITERS: %4d VARIANCE: %10.5lg STOPAT: %10.5lg\n",
               iter,variance,stopat);
        return variance<=stopat;
    }
    return false;
}

Mlsl::~Mlsl()
{
    //nothing here
}

int main()
{

    const int times =30;
    Statistics stat;

    for(int t=1;t<=times;t++)
    {
        srand(t);
        Test2nProblem p(4);
        Mlsl method(&p);
        method.setTerminationMethod("doublebox");
        method.Solve();
        stat.addProblem(&p);
    }


    stat.printStatistics();
    return 0;
}
