# include <stdio.h>
# include "kmeans.h"

int main(int argc,char **argv)
{
    Dataset set(argv[1]);

    //to 5 einai ena endeiktiko paradeigma omadon
    kmeans kt(&set,20);
    kt.runAlgorithm();
    kt.printStatistics();
    return 0;
}
