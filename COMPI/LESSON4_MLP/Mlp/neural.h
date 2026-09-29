#ifndef NEURAL_H
#define NEURAL_H

#include <dataset.h>
# include <problem.h>
class Neural : public Problem
{
private:
    Dataset *trainSet;
    Dataset *testSet;
    Data weight;
    double learningRate;
    int maxepochs;
    int nweight;
    string trainMethod="gd";//values: gd,gdwithls,siman
public:
    Neural();
    void    setTrainMethod(string s);
    string  getTrainmethod() const;
    void    setTrainSet(Dataset *t);
    void    setTestSet(Dataset *t);
    double  getLearningRate();
    void    setLearningRate(double x);
    int     getMaxEpochs();
    void    setMaxEpochs(int m);
    void    setWeights(Data &w);
    Data    getWeights();
    void    setNWeights(int n);
    double  sig(double x);
    double  sigder(double x);
    double  getOuput(Data &pattern);
    double  getClass(Data &pattern);
    double  getTrainError();
    double  getTestError();
    double  getClassError();
    void    train();
    Data    getDerivAtPoint(Data &x);
    Data    getDeriv();
    virtual double funmin(Data &x);
    virtual Data gradient(Data &x);
    virtual Data getSample();

    ~Neural();
};

#endif // NEURAL_H
