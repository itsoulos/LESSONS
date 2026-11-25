#ifndef POPULATION_H
#define POPULATION_H
# include <route.h>

class Population
{
private:
    QVector< QVector<int> > chromosome;
    QVector< QVector<int> > children;
    QVector<int> fitnessArray;
    double selection_rate,mutation_rate;
    Route *myroute;

    int     selectTournament();
    void    calculateFitness();
    void    sortChromosomes();
    void    crossover();
    void    mutate();
public:
    Population(Route *p,int count);
    void    setSelectionRate(double r);
    double  getSelectionRate();
    void    setMutationRate(double r);
    double  getMutationRate();
    void    nextGeneration();
    int     fitness(QVector<int> x);
    QVector<int>    bestChromosome();
    int             bestFitness();
};

#endif // POPULATION_H
