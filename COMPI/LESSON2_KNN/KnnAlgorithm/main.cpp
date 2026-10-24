#include <stdio.h>
# include <math.h>
# include "knn.h"
int main(int argc,char **argv)
{

    //einai to proto orisma tis grammis entolon (argv[1])
    Dataset train(argv[1]);
    Dataset test(argv[2]);

    Knn myKnn(&train,15);

    double total_class_error=0.0;
    double total_test_error = 0.0;
    //test.count() einai to plithos ton protypon sto test set
    for(int i=0;i<test.count();i++)
    {
        Data xx=test.getXPoint(i);
        double eclass = myKnn.getClass(xx);
        double evalue = myKnn.getValue(xx);
        double real_class = test.getClass(i);
        double real_value = test.getYPoint(i);
        total_class_error+=(fabs(eclass-real_class)>1e-5);
        total_test_error+=pow(real_value-evalue,2.0);
    }
    printf("Total Class error = %5.2lf%%\n",total_class_error*100.0/test.count());
    printf("Total Test  error = %5.2lf\n",total_test_error);
    return 0;
}
