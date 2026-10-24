#include "kmeans.h"
# include <math.h>
kmeans::kmeans(Dataset *d,int nteams)
{
    int i;
    dataset=d;
    team=nteams;
    center.resize(team);
    for(i=0;i<team;i++)
       center[i].resize(dataset->dimension());
    member.resize(dataset->count());
    for(i=0;i<member.size();i++)
        member[i]=-1;
}


//eukleidia apostasi
double  kmeans::distance(Data &x, Data &y)
{
    double s=0.0;
    int i;
    for(i=0;i<x.size();i++)
        s+=pow(x[i]-y[i],2.0);
    return sqrt(s);
}

void    kmeans::runAlgorithm()
{
    int i;
    initCenters();

    //se kathe epanalispsi kratao tin palia timi ton kentron
    //kai tin sygkrino me tin trexousa
    //an  den yparxei metaboli stamatao


    //to copycenters einai i palia timi ton kentron
    Matrix copyCenters;

    const int maxiterations=200;
    int iter=0;
    while(true)
    {
        copyCenters=center;
        for(i=0;i<member.size();i++)
        {
            Data x=dataset->getXPoint(i);
            int t=nearestTeam(x);
            member[i]=t;
        }
        updateCenters();
        double totalDistance=0.0;
        for(i=0;i<center.size();i++)
            totalDistance+=distance(center[i],copyCenters[i]);
        printf("Now TotalDistance= %20.10lf\n",totalDistance);
        if(totalDistance<1e-5) break;
        iter++;
        if(iter>=maxiterations) break;
    }
}

void    kmeans::printStatistics()
{
    //print for every pattern the associated team
    int i;
    int totalLoss=0;
    /*
    for(i=0;i<member.size();i++)
    {
        printf("Pattern:%4d Team: %4d Real Team: %lf\n",i,member[i],
               dataset->getYPoint(i)-1);
        if(fabs(member[i]-dataset->getYPoint(i)+1)>1e-5) totalLoss++;
    }
    printf("Total Lost patterns %4d\n",totalLoss);*/
    for(int i=0;i<center.size();i++)
    {
        printf("Center[%d]=",i);
        for(int j=0;j<center[i].size();j++)
            printf("%lf ",center[i][j]);
        printf("\n");
    }
}

void    kmeans::initCenters()
{
    int i;
    for(i=0;i<member.size();i++)
    {

        //esto oti anatheto kathe simeio se mia tyxaia omada
        member[i]=rand() % team;
        //enalaktika mporeite na valete ola ta simeia se ena kentro i enallax
        if(member[i]<0) member[i]=-member[i];
    }
    updateCenters();
}

int     kmeans::nearestTeam(Data &x)
{
    int i;
    double minDist=1e+100;
    int imin=-1;
    for(i=0;i<team;i++)
    {
        double dist=distance(x,center[i]);
        if(dist<minDist)
        {
            minDist=dist;
            imin=i;
        }
    }
    return imin;
}


//edo enimerono ta kentra

void    kmeans::updateCenters()
{
 int i,j;

 //bazo ta kentra se 0.0, simeiosi ta kentra einai mesoi oroi
 for(i=0;i<team;i++)
 {
     for(j=0;j<center[i].size();j++)
         center[i][j]=0.0;
 }

 //o pinakas aytos katagrafei posa simeia exei kathe kentro

 vector<int> teamMembers;
 teamMembers.resize(team);
 for(int i=0;i<teamMembers.size();i++)
     teamMembers[i]=0;

 for(i=0;i<member.size();i++)
 {
     teamMembers[member[i]]++;
 }


 //edo ksekinaei o ypologismos ton meson oron
 for(i=0;i<member.size();i++)
 {
     Data x=dataset->getXPoint(i);
     int whatTeam=member[i];
     for(j=0;j<x.size();j++)
     {
         center[whatTeam][j]+=x[j]/teamMembers[whatTeam];
         //center[whatTeam][j]=center[whatTeam][j]+x[j]/teamMembers[whatTeam];
     }
 }
}
