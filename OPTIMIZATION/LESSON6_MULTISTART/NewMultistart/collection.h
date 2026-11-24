#ifndef COLLECTION_H
#define COLLECTION_H
# include "problem.h"

class Collection
{
private:
    Matrix xdata;
    Data   ydata;
public:
    /**
     * @brief Collection Synartisi dimioyrgias
     */
    Collection();
    /**
     * @brief addPoint prosthetei ena neo simeio stin syllogi
     * @param x
     * @param y
     */
    void    addPoint(Data &x,double &y);
    /**
     * @brief getPoint Epistrefei ena simeio sto deigma
     * @param pos
     * @param x
     * @param y
     */
    void    getPoint(int pos,Data &x,double &y);
    /**
     * @brief haveGraphMinima Epistrefei alithes an exei graph minima mesa sto deigma
     * @param x
     * @param y
     * @param distance
     * @return
     */
    bool    haveGraphMinima(Data &x,double &y,double distance);
    /**
     * @brief resizeInFraction krataei ta fraction % kalytera simeia sto deigma
     * @param fraction
     */
    void    resizeInFraction(double fraction);
    /**
     * @brief getSize epistrefei to plithos ton simeion stin syllogi
     * @return
     */
    int     getSize() const;

    /**
     * @brief getDistance Eyklidia apostasi
     * @param x
     * @param y
     * @return
     */
    double  getDistance(Data &x,Data &y);

    /**
     * @brief isPointIn epistrefei alithes an ena deigma yparxei idi mesa
     * @param x
     * @param y
     * @return
     */
    bool isPointIn(Data x);
    /** Synartisi diagrafis
     */

    void    replacePoint(int pos,Data &x,double &y);
    void    getBestWorstValues(double &besty,double &worsty);
    ~Collection();
};
#endif // COLLECTION_H
