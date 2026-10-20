#ifndef SIMPLEXMETHOD_H
#define SIMPLEXMETHOD_H

# include <problem.h>

class SimplexMethod
{
private:
    Matrix xpoint;
    Data ypoint;
    Problem *myProblem;
    Data xc, xr;
    double fc, fr;
    double alpha, beta, gamma;
    Data getCentroid();
    Data getReflected(Data &centroid);
    void sortPoints();
    double getMeanf();
    double getVariancef();
    void insertionStep();
    void stretchingStep();
    void contractionStep();
    bool savePointsFlag =false;
public:
    SimplexMethod(Problem *p);
    void    enableSavePoints();
    void setAlpha(double a);
    double getAlpha() const;
    void setBeta(double b);
    double getBeta() const;
    void setGamma(double g);
    double getGamma() const;
    void runAlgorithm();
    Data getBestx();

    void    savePointsInFile(const char *filename);
    ~SimplexMethod();
};

#endif // SIMPLEXMETHOD_H
