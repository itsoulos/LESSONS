#include "dataset.h"

int main(int argc, char *argv[])
{
    Dataset tx(argv[1]);
    tx.normalizeMinMax();
    tx.saveData("test.txt");
    return 0;
}
