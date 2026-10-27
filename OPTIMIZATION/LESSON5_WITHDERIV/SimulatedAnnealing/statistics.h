#ifndef STATISTICS_H
#define STATISTICS_H
# include "problem.h"
class Statistics
{
private:
    /**
     * @brief bestyValue o pinakas me tis kalyteres times apo tis ekteleseis
     */
    Data bestyValue;
    /**
     * @brief fcallsValue o pinakas me tis kliseis stin synartisi anamesa stis
     * ektelseis.
     */
    vector<int> fcallsValue;
public:
    /**
     * @brief Statistics i synartisi dimioyrgias
     */
    Statistics();
    /**
     * @brief addProblem prosthetei to problima ston pinaka statistikon
     * @param p
     */
    void addProblem(Problem *p);
    /**
     * @brief printStatistics ektyponei stin othoni tis metriseis
     */
    void printStatistics();
    ~Statistics();
};


#endif // STATISTICS_H
