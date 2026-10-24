#include "knn.h"


/** constructor of the Knn class **/
Knn::Knn(Dataset *t,int K)
{
    dt = t;
    paramK=K;
}


/** Epistrefei apostasi metaxy x1,x2 **/
double  Knn::getDistance(Data &x1,Data &x2)
{
    double sum =0.0;
    for(int i=0;i<x1.size();i++)
        sum+=(x1[i]-x2[i])*(x1[i]-x2[i]);//pow(x1[i]-x2[i],2.0);
    return sqrt(sum);
}

vector<KnnRecord>   Knn::getNeighbours(Data &x)
{
    vector<KnnRecord> table;
    for(int i=0;i<dt->count();i++)
    {
        KnnRecord t;
        Data x1 = dt->getXPoint(i);
        t.distance = getDistance(x1,x);
        t.classValue = dt->getYPoint(i);
        table.push_back(t);
    }
    return table;
}

void                Knn::sortNeighbours(vector<KnnRecord> &x)
{
    for(int i=0;i<(int)x.size();i++)
    {
        for(int j=0;j<(int)x.size()-1;j++)
        {
            if(x[j+1].distance<x[j].distance)
            {
                KnnRecord t1 = x[j];
                x[j]=x[j+1];
                x[j+1]=t1;
            }
        }
    }
}

vector<KnnRecord>   Knn::getKNeighbours(Data &pattern)
{
    vector<KnnRecord> table;
    vector<KnnRecord> x = getNeighbours(pattern);
    sortNeighbours(x);
    for(int i=0;i<paramK;i++)
    {
        table.push_back(x[i]);
    }
    return table;
}

double      Knn::getClass(Data &x)
{
    vector<KnnRecord> myknn = getKNeighbours(x);
    vector<int> mvote;
    //vote
    mvote.resize(dt->getNumberOfClasses());
    for(int i=0;i<(int)mvote.size();i++)
    {
        mvote[i]=0;
    }
    for(int i=0;i<paramK;i++)
    {
        mvote[dt->getNearestClassIndex(myknn[i].classValue)]++;
    }
    //find maximum vote
    int maxVote = mvote[0];
    int maxVotePos = 0;
    for(int i=0;i<mvote.size();i++)
    {
        if(mvote[i]>maxVote)
        {
            maxVote = mvote[i];
            maxVotePos =i;
        }
    }
    return dt->getPatternClass()[maxVotePos];
}

double      Knn::getValue(Data &x)
{
    vector<KnnRecord> myknn = getKNeighbours(x);
    double meanValue = 0.0;
    for(int i=0;i<paramK;i++)
        meanValue+=myknn[i].classValue;
    meanValue/=paramK;
    return meanValue;
}


Knn::~Knn()
{

}
