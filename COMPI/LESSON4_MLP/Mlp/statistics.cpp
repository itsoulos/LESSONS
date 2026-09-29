#include "statistics.h"

Statistics::Statistics()
{
}

void Statistics::addNeural(Neural *p)
{
    trainError.push_back(p->getTrainError());
    testError.push_back(p->getTestError());
    classError.push_back(p->getClassError());
}

void Statistics::printStatistics()
{
        double avg_train_error = 0.0;
        double avg_class_error = 0.0;
        double avg_test_error  = 0.0;
        for(int i=0;i<trainError.size();i++)
        {
            avg_train_error+=trainError[i];
            avg_test_error+=testError[i];
            avg_class_error+=classError[i];
        }
        printf("Number of executions %4d\n",trainError.size());
        printf("TRAIN ERROR=%20.10lg\n",avg_train_error/trainError.size());
        printf("TEST  ERROR=%20.10lg\n",avg_test_error/testError.size());
        printf("CLASS ERROR=%20.2lf%%\n",avg_class_error/classError.size());
}

Statistics::~Statistics()
{

}
