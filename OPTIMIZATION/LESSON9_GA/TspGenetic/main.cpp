# include <population.h>

int main(int argc, char *argv[])
{
    Route myroute(5);
    myroute.addCost(0,1,10);
    myroute.addCost(0,2,150);
    myroute.addCost(0,3,60);
    myroute.addCost(0,4,20);
    myroute.addCost(1,2,200);
    myroute.addCost(1,3,6);
    myroute.addCost(1,4,170);
    myroute.addCost(2,3,10);
    myroute.addCost(2,4,8);
    myroute.addCost(3,4,60);
    Population pop(&myroute,20);
    const int maxgenerations=200;
    int i;
    for(i=1;i<=maxgenerations;i++)
    {
        pop.nextGeneration();
        int f=pop.bestFitness();
        printf("Generation:%4d Fitness:%4d\n",i,f);
        QVector<int> x=pop.bestChromosome();
        int j;
        for(j=0;j<x.size();j++)
        {
            printf("%d ",x[j]);
            if(j!=x.size()-1) printf("->");
        }
        printf("\n");
    }
    return 0;
}
