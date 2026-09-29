#ifndef RBF_H
#define RBF_H
# include <dataset.h>
# include <kmeans.h>
class Rbf
{
private:
    Data weight;
    Matrix centroid;
    Data variance;

    Dataset *trainSet,*testSet;
    int   nweights;//centroids
    int   pattern_dimension;
     Data    classVector;
    void    init_arrays();
    double  gauss_function(Data &pattern,Data &center,double sigma);
    Matrix  matrix_transpose(Matrix &x);
    Matrix  matrix_mult(Matrix &x,Matrix &y);
    Matrix  matrix_inverse(Matrix x);
    Matrix  matrix_pseudoinverse(Matrix &x);
public:
    Rbf();
    void    setNumberOfWeights(int K);
    int     getNumberOfWeights();
    void    setTrainSet(Dataset *t);
    void    setTestSet(Dataset *t);
    void    train();
    double  getOutput(Data &pattern);
    double  getClass(Data &pattern);
    double  getTrainError();
    double  getTestError();
    double  getClassError();
    double  product(Data &x,Data &y);
};

#endif // RBF_H
