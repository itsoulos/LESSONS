#ifndef ROUTE_H
#define ROUTE_H
# include <QVector>


class Route
{
private:
   int cities;
   QVector< QVector<int> > costArray;
public:
    Route(int c);
    void addCost(int start,int end,int value);
    QVector<int> randomRoute();
    void    mutateRoute(QVector<int> &x,int pos);
    QVector<int> crossoverRoute(QVector<int> x1,QVector<int> x2);
    int cost(QVector<int> x);
    int  getCities();
};

#endif // ROUTE_H
