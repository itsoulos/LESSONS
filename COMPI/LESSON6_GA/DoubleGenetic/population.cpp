#include "population.h"
Population::Population(Problem *p,int count)
{
    myproblem=p;
    chromosome.resize(count);
    int i;
    fitnessArray.resize(count);
    children.resize(count);
    for(i=0;i<count;i++)
    {
        chromosome[i].resize(myproblem->getDimension());
        children[i].resize(myproblem->getDimension());
        chromosome[i]=myproblem->getSample();
    }
    calculateFitness();
    selection_rate=0.1;
    mutation_rate=0.05;
}

void    Population::setSelectionRate(double r)
{
    if(r>=0 && r<=1)
        selection_rate=r;
}

double  Population::getSelectionRate() const
{
    return selection_rate;
}

void    Population::setMutationRate(double r)
{
    if(r>=0 && r<=1)
        mutation_rate=r;
}

double  Population::getMutationRate() const
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

double  Population::fitness(Data x)
{
    return myproblem->funmin(x);
}

void    Population::sortChromosomes()
{
    Data g;
    g.resize(myproblem->getDimension());
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

void    Population::calculateFitness()
{
    int i;
    for(i=0;i<chromosome.size();i++)
        fitnessArray[i]=fitness(chromosome[i]);
}

void    Population::mutate()
{
    int i;
    for(i=1;i<chromosome.size();i++)
    {
        for(int j=0;j<myproblem->getDimension();j++)
        {
            double r=rand() *1.0/RAND_MAX;
            if(r<mutation_rate)
                myproblem->mutate(chromosome[i],j);
        }
    }
}

void    Population::crossover()
{
    int nchildren=(1.0 - selection_rate)*chromosome.size();
    int count_children=0;
    while(count_children<nchildren)
    {
        int parent1=selectRoulete();
        int parent2=selectRoulete();
        Data x1=chromosome[parent1];
        Data x2=chromosome[parent2];
        children[count_children++]=uniformCrossover(x1,x2);
    }
    int i;
    for(i=0;i<nchildren;i++)
        chromosome[chromosome.size()-i-1]=children[i];
}

int     Population::selectTournament()
{
    const int K=8;
    int bestIndex=-1;
    double bestFitness=1e+100;
    int i;
    for(i=1;i<=K;i++)
    {
        int parent=rand() % chromosome.size();
        if(fitnessArray[parent]<bestFitness)
        {
            bestFitness=fitnessArray[parent];
            bestIndex=parent;
        }
    }
    return bestIndex;
}

int     Population::selectRoulete()
{
    double sumFitness=0.0;
    int i;
    //normalize and sort fitness
    Data copyFitness=fitnessArray;
    double fmin=-copyFitness[0],fmax=-copyFitness[0];
    for(i=0;i<copyFitness.size();i++)
    {
        //min will become max
        copyFitness[i]=-copyFitness[i];
        if(copyFitness[i]>fmax) fmax=copyFitness[i];
        if(copyFitness[i]<fmin) fmin=copyFitness[i];
    }
    for(i=0;i<copyFitness.size();i++)
    {
        copyFitness[i]=(copyFitness[i]-fmin)/(fmax-fmin);
    }
    for(i=0;i<fitnessArray.size();i++) sumFitness+=copyFitness[i];
    double rnd=(rand()*1.0/RAND_MAX)*sumFitness;
    double sum=0.0;
    for(i=0;i<copyFitness.size();i++)
    {
        sum+=copyFitness[i];
        if(sum>=rnd) return i;
    }
    return copyFitness.size()-1;
}

Data    Population::uniformCrossover(Data x1,Data x2)
{
    Data g;
    g.resize(x1.size());
    int i;
    for(i=0;i<g.size();i++)
    {
        int r=rand() %2;
        if(r==0) g[i]=x1[i];
        else     g[i]=x2[i];
    }
    return g;
}

Data    Population::doubleCrossover(Data x1,Data x2)
{
    Data g;
    g.resize(x1.size());
    int i;
    for(i=0;i<g.size();i++)
    {
        double r=rand() *1.0/RAND_MAX;
        g[i]=r*x1[i]+(1.0-r)*x2[i];
    }
    return g;
}


Data    Population::bestChromosome()
{
    return chromosome[0];
}

double  Population::bestFitness()
{
    return fitnessArray[0];
}
