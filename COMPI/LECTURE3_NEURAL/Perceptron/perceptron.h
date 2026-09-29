#ifndef PERCEPTRON_H
#define PERCEPTRON_H
# include <dataset.h>

class Perceptron
{
private:
    /** trainSet: to train set ton data
     *  testSet:  to test set ton data **/
    Dataset *trainSet;
    Dataset *testSet;
    double n;//rythmos mathisis

    //einai o pinakas varon
    Data weight;

    //megistos arithmos epanalipseon
    int  emax;
public:
    Perceptron();
    Perceptron(Dataset *tr,Dataset *tt);
    void setTrainSet(Dataset *t);
    void setTestSet(Dataset *t);
    void setN(double mn);
    double getN() const;
    void setEmax(int e);
    int  getEmax() const;
    void train();
    double getClass(Data pattern);
    double testError();

    //einai to esoteriko ginomeno
    double product(Data x,Data y);

    //eykleidia apostasi
    double distance(Data x,Data y);
};

#endif // PERCEPTRON_H
