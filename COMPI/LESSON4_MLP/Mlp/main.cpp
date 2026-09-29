#include <neural.h>
#include <stdlib.h>
# include <statistics.h>
int main(int argc, char *argv[])
{
    Dataset train(argv[1]);
    Dataset test(argv[2]);
    Statistics stat;
    for(int iters=1;iters<=30;iters++)
    {
        srand(iters);
        Neural mymlp;
        mymlp.setTrainMethod("gd");
        mymlp.setTrainSet(&train);
        mymlp.setTestSet(&test);
        mymlp.setNWeights(10);
        mymlp.setLearningRate(0.0001);
        mymlp.setMaxEpochs(200);
        mymlp.train();
        stat.addNeural(&mymlp);
    }
    stat.printStatistics();
    return 0;
}
