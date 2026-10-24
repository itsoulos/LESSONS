#ifndef KNN_H
#define KNN_H
# include "dataset.h"

/**
 *  Stin klassi KnnRecord apothikeytai i apostasi apo
 *  to protypo anaforas kai i katigoria autou tou geitona.
 */
typedef struct KnnRecord
{
    double  distance;
    double  classValue;
};
class Knn
{
private:
    /**
     * @brief dt, to dataset gia training
     */
    Dataset *dt;
    /**
     * @brief paramK, i parametros K
     */
    int paramK;
    /**
     * @brief getNeighbours, epistrefei pinaka apostaseon gia to protypo x
     * @param x
     * @return
     */
    vector<KnnRecord>   getNeighbours(Data &x);
    /**
     * @brief sortNeighbours, taxinomei tous geitones se auxousa seira os
     * pros tin apostasi
     * @param x
     */
    void                sortNeighbours(vector<KnnRecord> &x);
    /**
     * @brief getKNeighbours, epistrefei san yposynolo tous protous
     * k geitones
     * @param x
     * @return
     */
    vector<KnnRecord>   getKNeighbours(Data& pattern);
public:
    /**
     * @brief Knn, synartisi dimiourgias
     * @param t
     * @param K
     */
    Knn(Dataset *t,int K);
    /**
     * @brief getClass, epistrefei tin klasi tou protypou x
     * @param x
     * @return
     */
    double      getClass(Data &x);
    /**
     * @brief getValue, epistrefei tin ektimomeni exodo enos protypou x
     * @param x
     * @return
     */
    double      getValue(Data &x);
    /**
     * @brief getDistance, euclidia apostasi
     * @param x1
     * @param x2
     * @return
     */
    double      getDistance(Data &x1,Data &x2);
    ~Knn();
};

#endif // KNN_H
