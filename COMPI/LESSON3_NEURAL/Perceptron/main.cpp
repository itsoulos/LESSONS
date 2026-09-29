# include <perceptron.h>
int main(int argc, char *argv[])
{

    Dataset trainSet(argv[1]);
    Dataset testSet(argv[2]);
    Perceptron p;
    srand(2);
    p.setEmax(100);
    p.setN(0.01);
    p.setTrainSet(&trainSet);
    p.setTestSet(&testSet);
    p.train();
    double tt=p.testError();
    printf("Test Error= %lf%%\n",tt);
   return 0;
}
