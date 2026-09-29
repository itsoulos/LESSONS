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
    Matrix xpoint;
    Data   ypoint;
public:
    Dataset();
    Dataset(char *filaname);
    void    setData(Matrix &x,Data &y);
    void    saveData(char *filename);
    Data    getXPoint(int pos) const;
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
};

#endif // DATASET_H
