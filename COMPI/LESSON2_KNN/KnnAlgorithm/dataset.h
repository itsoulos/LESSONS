#ifndef DATASET_H
#define DATASET_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <vector>
using namespace std;

//to Data einai ena pattern
typedef vector<double> Data;
//double *x;
//vector<double> STL
//vector<int> vector<Person>

//didiastatos pinakas
typedef vector<Data>   Matrix;
//double **A

class Dataset
{
private:
    // xpoint = > ta protypa
    Matrix xpoint;

    //oi monadikes katigories sta protypa
    Data patternClass;
    //sto pararadeigma tou wine sto patternClass mpainoune mesa treis times 0, 0.5, 1.0
    /** **/
    //
    // ypoint = > exodos gia kathe protypo
    Data   ypoint;
    /**
     * @brief makePatternClass, dimiourgei tis monadikes katigories pou
     * exei to problima.
     */
    void makePatternClass();
public:
    /**
     * @brief Dataset, default sinartisi dimiourgias
     */
    Dataset();
    /**
     * @brief Dataset, fortonei apo to filename ta protypa tou problimatos
     * @param filaname
     */
    Dataset(char *filaname);
    /**
     * @brief setData, allazei tous pinakes x,y
     * @param x
     * @param y
     */
    void    setData(Matrix &x,Data &y);
    /**
     * @brief saveData, apothikeyei ta protypa se arxeio
     * @param filename
     */
    void    saveData(char *filename);

    /**
     * @brief getXPoint, epistrefei to protypo stin thesi pos
     * @param pos
     * @return
     */
    Data    getXPoint(int pos) const;

    /**
     * @brief getYPoint, epistrefei tin exodo gia to protypo stin thesi pos
     * @param pos
     * @return
     */
    double  getYPoint(int pos) const;
    /**
     * @brief maxx, epistrefei tin megisti timi sto feature pos
     * @param pos
     * @return
     */
    double  maxx(int pos) const;
    /**
     * @brief minx, epistrefei tin elaxisti timi sto feature pos
     * @param pos
     * @return
     */
    double  minx(int pos) const;
    /**
     * @brief miny, elaxisti timi stin exodo
     * @return
     */
    double  miny() const;
    /**
     * @brief maxy, megisti timi stin exodo
     * @return
     */
    double  maxy() const;
    /**
     * @brief meanx, mesos oros timon gia to feature pos
     * @param pos
     * @return
     */
    double  meanx(int pos) const;
    /**
     * @brief stdx, standard deviation gia to feature pos
     * @param pos
     * @return
     */
    double  stdx(int pos) const;
    /**
     * @brief meany, mesos oros gia tin exodo
     * @return
     */
    double  meany() const;
    /**
     * @brief stdy, standard deviation gia tin exodo
     * @return
     */
    double  stdy() const;
    /**
     * @brief count, plithos protypon
     * @return
     */
    int     count() const;
    /**
     * @brief dimension, arithmos features
     * @return
     */
    int     dimension() const;
    /**
     * @brief normalizeMinMax, kanonikopoiisi dataset
     */
    void    normalizeMinMax();
    /**
     * @brief getPatternClass, epistrefei ton pinaka klaseon
     * @return
     */
    Data    getPatternClass();
    /**
     * @brief getClass, epistrefei tin klasi se mia thesi
     * @param pos
     * @return
     */
    double  getClass(int pos) const;

    /** Epistrefei tin kontinoteri katigoria gia tin timi value **/
    double  getNearestClass(double value) const;
    /**
     * @brief getNearestClassIndex, briskei tin thesi ston pinaka
     * classeon gia tin timi value
     * @param value
     * @return
     */
    int     getNearestClassIndex(double value) const;
    /**
     * @brief getNumberOfClasses, epistrefei to plithos ton klaseon
     * @return
     */
    int     getNumberOfClasses() const;
};

#endif // DATASET_H
