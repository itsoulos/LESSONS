# include <adaline.h>
int main(int argc, char *argv[])
{
    Dataset train(argv[1]);
    Dataset test(argv[2]);
    Adaline ada;
    ada.setMaxEpochs(200);
    ada.setN(0.001);
    ada.setTrainSet(&train);
    ada.setTestSet(&test);
    ada.train();
    double e=ada.getTestError();
    double c=ada.getClassError();
    int i;
    for(i=0;i<test.count();i++)
    {
        Data pattern=test.getXPoint(i);
        pattern.push_back(1.0);
        double value=ada.getOutput(pattern);
        printf("%lf %lf %lf \n",pattern[0],test.getYPoint(i),value);
    }
   return 0;
}
