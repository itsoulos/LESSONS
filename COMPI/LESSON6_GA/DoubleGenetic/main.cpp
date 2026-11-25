# include <population.h>
# include <math.h>
class RastriginProblem :public Problem
{
public:
    RastriginProblem() :Problem(2)
    {
        Data x1,x2;
        x1.resize(2);
        x2.resize(2);
        x1[0]=-1;x1[1]=-1;
        x2[0]= 1;x2[1]= 1;
        setLeftMargin(x1);
        setRightMargin(x2);
    }

virtual double funmin(Data x)
    {
     return x[0]*x[0]+x[1]*x[1]-cos(18.0*x[0])-cos(18.0*x[1]);
    }
};

int main(int argc, char *argv[])
{
    RastriginProblem p;
    Population pop(&p,200);
    const int maxgenerations=200;
    int i;
    for(i=1;i<=maxgenerations;i++)
    {
        pop.nextGeneration();
        double f=pop.bestFitness();
        printf("Iteration: %4d Fitness: %10.4lf\n",i,f);
    }
   return 0;
}
