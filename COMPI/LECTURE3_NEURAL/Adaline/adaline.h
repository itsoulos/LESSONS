#ifndef ADALINE_H
#define ADALINE_H
# include <dataset.h>

class Adaline
{
private:
    Dataset *trainSet;
    Dataset *testSet;
    Data    weight;

    //einai oi monadikes klaseis tou problimatos
    Data    classVector;
    double n;//learning rate

    //megistos arithmos epanalipseon
    int    maxepochs;
public:
    Adaline();
    void setTrainSet(Dataset *t);
    void setTestSet(Dataset *t);
    void setN(double mn);
    double getN() const;
    void setMaxEpochs(int e);
    int  getMaxEpochs() const;
    void train();
    double getTrainError();
    double getTestError();
    double getClassError();
    double getOutput(Data pattern);
    double getClass(Data pattern);
    double product(Data x,Data y);
};

#endif // ADALINE_H
