#ifndef DATASET_H
#define DATASET_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <vector>
using namespace std;

typedef vector<double> Data;
typedef vector<Data>   Matrix;
class Dataset
{
private:
    // xpoint = > ta protypa
    Matrix xpoint;

    //oi monadikes katigories sta protypa
    Data patternClass;
    /** **/
    //
    // ypoint = > exodos gia kathe protypo
    Data   ypoint;
    void makePatternClass();
public:
    Dataset(); // => default synartisi dimiourgias
    Dataset(char *filaname);
    void    setData(Matrix &x,Data &y);
    void    saveData(char *filename);

    //epistrefei pattern
    Data    getXPoint(int pos) const;

    //epistrefei mia exodo
    double  getYPoint(int pos) const;
    double  maxx(int pos) const;
    double  minx(int pos) const;
    double  miny() const;
    double  maxy() const;
    double  meanx(int pos) const;
    double  stdx(int pos) const;
    double  meany() const;
    double  stdy() const;
    int     count() const;
    int     dimension() const;
    void    normalizeMinMax();
    Data    getPatternClass();
    double  getClass(int pos) const;
};

#endif // DATASET_H
