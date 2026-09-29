# include <rbf.h>

int main(int argc, char *argv[])
{
    Dataset train(argv[1]);
    Dataset test(argv[2]);
    Rbf myrbf;
    srand(3);

    myrbf.setTrainSet(&train);
    myrbf.setTestSet(&test);
    myrbf.setNumberOfWeights(20);
    myrbf.train();
    double trainError =myrbf.getTrainError();
    double testError  =myrbf.getTestError();
    double classError =myrbf.getClassError();
    printf("TrainError: %8.5lf TestError: %8.5lf ClassError: %8.5lf\n",
           trainError,testError,classError);

    return 0;
}
