#ifndef STATISTICS_H
#define STATISTICS_H
# include "neural.h"
class Statistics
{
private:
    Data trainError;
    Data testError;
    Data classError;
public:
    Statistics();
    void addNeural(Neural *p);
    void printStatistics();
    ~Statistics();
};


#endif // STATISTICS_H
