#ifndef KMEANS_H
#define KMEANS_H
# include <dataset.h>

class kmeans
{
private:
    /**
      dataset: To dataset me ta dedomena
      center : to kentro kathe omadas
      member : gia kathe protypo se poia omada einai
      team   : to plithos omadon
    */
    Dataset *dataset;
    Matrix center;//double **center;
    vector<int>  member;
    int team;
    vector<int> teamMembers;


    void initCenters();
    int  nearestTeam(Data &x);
    void updateCenters();
    double distance(Data &x,Data &y);
public:
    kmeans(Dataset *d,int nteams);
    void    runAlgorithm();
    vector<Data> getCenters();
    Data          getVariances();
};

#endif // KMEANS_H
