#include "population.h"
Population::Population(Route *p,int count)
{
    myroute=p;
    chromosome.resize(count);
    children.resize(count);
    fitnessArray.resize(count);
    int i;
    for(i=0;i<count;i++)
    {
        chromosome[i].resize(myroute->getCities());
        children[i].resize(myroute->getCities());
        chromosome[i]=myroute->randomRoute();
    }
    calculateFitness();
    selection_rate=0.10;
    mutation_rate=0.05;
}

void    Population::setSelectionRate(double r)
{
    if(r>=0 && r<=1) selection_rate=r;
}

double  Population::getSelectionRate()
{
    return selection_rate;
}

void    Population::setMutationRate(double r)
{
    if(r>=0 && r<=1) mutation_rate=r;
}

double  Population::getMutationRate()
{
    return mutation_rate;
}

void    Population::nextGeneration()
{
    calculateFitness();
    sortChromosomes();
    crossover();
    mutate();

}

int     Population::fitness(QVector<int> x)
{
    return myroute->cost(x);
}

QVector<int>    Population::bestChromosome()
{
    return chromosome[0];
}

int   Population::bestFitness()
{
    return fitnessArray[0];
}

int     Population::selectTournament()
{
    const int K=8;
    int bestIndex=-1;
    int bestFitness=1000000;
    int i;
    for(i=1;i<=K;i++)
    {
        int parent=rand() % chromosome.size();
        if(i==1 || fitnessArray[parent]<bestFitness)
        {
            bestFitness=fitnessArray[parent];
            bestIndex=parent;
        }
    }
    return bestIndex;
}

void    Population::calculateFitness()
{
    int i;
    for(i=0;i<chromosome.size();i++)
        fitnessArray[i]=fitness(chromosome[i]);
}

void    Population::sortChromosomes()
{
    QVector<int> g;
    g.resize(myroute->getCities());
    int i,j;
    for(i=0;i<chromosome.size();i++)
    {
        for(j=0;j<chromosome.size()-1;j++)
        {
            if(fitnessArray[j+1]<fitnessArray[j])
            {
                double f=fitnessArray[j];
                fitnessArray[j]=fitnessArray[j+1];
                fitnessArray[j+1]=f;
                g=chromosome[j];
                chromosome[j]=chromosome[j+1];
                chromosome[j+1]=g;
            }
        }
    }
}

void    Population::crossover()
{
    int nchildren=(1.0 - selection_rate)*chromosome.size();
    int count_children=0;
    while(count_children<nchildren)
    {
        int parent1=selectTournament();
        int parent2=selectTournament();
        QVector<int> x1=chromosome[parent1];
        QVector<int> x2=chromosome[parent2];
        children[count_children++]=myroute->crossoverRoute(x1,x2);
    }
    int i;
    for(i=0;i<nchildren;i++)
        chromosome[chromosome.size()-i-1]=children[i];
}

void    Population::mutate()
{
    int i,j;
    for(i=1;i<chromosome.size();i++)
    {
        for(j=0;j<myroute->getCities();j++)
        {
            double r=rand()*1.0/RAND_MAX;
            if(r<mutation_rate)
                myroute->mutateRoute(chromosome[i],j);
        }
    }
}
