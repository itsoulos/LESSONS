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

    //pinakas apo pinakes
    vector<Data> center;

    //katagrafei gia kathe protypo se poia omada anikei
    vector<int>  member;

    //to team einai poses omades exo
    int team;

    void initCenters();

    //briskei se poia omada einai pio konta ena simeio
    int  nearestTeam(Data &x);

    //enimerosi ton kentron kai pali
    void updateCenters();


    //eukleidia apostasi
    double distance(Data &x,Data &y);
public:
    kmeans(Dataset *d,int nteams);
    void    runAlgorithm();
    void    printStatistics();
};

#endif // KMEANS_H
