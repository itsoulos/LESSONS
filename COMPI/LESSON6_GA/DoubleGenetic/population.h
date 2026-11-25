#ifndef POPULATION_H
#define POPULATION_H
# include <problem.h>
class Population
{
private:
    Data fitnessArray;
    QVector<Data> chromosome;
    QVector<Data> children;
    double  mutation_rate;
    double  selection_rate;
    Problem *myproblem;

    double  fitness(Data x);
    void    sortChromosomes();
    void    calculateFitness();
    void    mutate();
    void    crossover();
    int     selectTournament();
    int     selectRoulete();
    Data    uniformCrossover(Data x1,Data x2);
    Data    doubleCrossover(Data x1,Data x2);
public:
    Population(Problem *p,int count);
    void    setSelectionRate(double r);
    double  getSelectionRate() const;
    void    setMutationRate(double r);
    double  getMutationRate() const;
    void    nextGeneration();
    Data    bestChromosome();
    double  bestFitness();
};

#endif // POPULATION_H
