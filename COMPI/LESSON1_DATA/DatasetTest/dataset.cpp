#include "dataset.h"

Dataset::Dataset()
{
    xpoint.resize(0);
    ypoint.resize(0);
}

Dataset::Dataset(char *filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return;
    int d,count;
    fscanf(fp,"%d",&d);
    fscanf(fp,"%d",&count);
    ypoint.resize(count);
    xpoint.resize(count);
    for(int i=0;i<count;i++)
    {
        xpoint[i].resize(d);
        for(int j=0;j<d;j++)
            fscanf(fp,"%lf",&xpoint[i][j]);
        fscanf(fp,"%lf",&ypoint[i]);
    }
    fclose(fp);
}

void    Dataset::setData(Matrix &x,Data &y)
{
    if(x.size()!=y.size()) return;
    xpoint.resize(x.size());
    ypoint.resize(y.size());
    int d=x[0].size();
    for(int i=0;i<x.size();i++)
    {
        xpoint[i].resize(d);
        for(int j=0;j<d;j++)
            xpoint[i][j]=x[i][j];
        ypoint[i]=y[i];
    }
}

void    Dataset::saveData(char *filename)
{
    FILE *fp=fopen(filename,"w");
    if(!fp) return;
    fprintf(fp,"%d\n%d\n",dimension(),count());
    for(int i=0;i<count();i++)
    {
        for(int j=0;j<dimension();j++)
            fprintf(fp,"%lf ",xpoint[i][j]);
        fprintf(fp,"%lf\n",ypoint[i]);
    }
    fclose(fp);
}

Data    Dataset::getXPoint(int pos) const
{
    if(pos<0 || pos>=count()) return xpoint[0];
    return xpoint[pos];
}

double  Dataset::getYPoint(int pos) const
{
    if(pos<0 || pos>=count()) return -1;
    return ypoint[pos];
}

double  Dataset::meanx(int pos) const
{
    if(pos<0 || pos>=count()) return -1;
    double s=0.0;
    for(int i=0;i<xpoint.size();i++)
        s+=xpoint[i][pos];
    return s/xpoint.size();
}

double  Dataset::stdx(int pos) const
{
    if(pos<0 || pos>=count()) return -1;
    double s=0.0;
    double mx=meanx(pos);
    for(int i=0;i<xpoint.size();i++)
        s+=(xpoint[i][pos]-mx)*(xpoint[i][pos]-mx);
    return sqrt(1.0/xpoint.size() * s);
}

double  Dataset::meany() const
{
    double s=0.0;
    for(int i=0;i<ypoint.size();i++)
        s+=ypoint[i];
    return s/ypoint.size();
}

double  Dataset::stdy() const
{
  double my=meany();
  double s=0.0;
  for(int i=0;i<ypoint.size();i++)
      s+=(ypoint[i]-my)*(ypoint[i]-my);
  return sqrt(1.0/ypoint.size() * s);
}

double  Dataset::maxx(int pos) const
{
    double m=xpoint[0][pos];
    for(int i=0;i<xpoint.size();i++)
        if(xpoint[i][pos]>m) m=xpoint[i][pos];
    return m;
}

double  Dataset::minx(int pos) const
{
    double m=xpoint[0][pos];
    for(int i=0;i<xpoint.size();i++)
        if(xpoint[i][pos]<m) m=xpoint[i][pos];
    return m;
}

double  Dataset::miny() const
{
    double m=ypoint[0];
    for(int i=0;i<ypoint.size();i++)
        if(ypoint[i]<m) m=ypoint[i];
    return m;
}

double  Dataset::maxy() const
{
    double m=ypoint[0];
    for(int i=0;i<ypoint.size();i++)
        if(ypoint[i]>m) m=ypoint[i];
    return m;
}

int     Dataset::count() const
{
    return ypoint.size();
}

int     Dataset::dimension() const
{
    return xpoint[0].size();
}

void    Dataset::normalizeMinMax()
{
    Data MinX,MaxX;
    double MinY,MaxY;
    MinX.resize(dimension());
    MaxX.resize(dimension());
    for(int i=0;i<dimension();i++)
    {
        MinX[i]=minx(i);
        MaxX[i]=maxx(i);
    }
    MinY=miny();
    MaxY=maxy();
    for(int i=0;i<count();i++)
    {
        for(int j=0;j<dimension();j++)
        {
            xpoint[i][j]=(MaxX[j]-xpoint[i][j])/(MaxX[j]-MinX[j]);
        }
        ypoint[i]=(MaxY-ypoint[i])/(MaxY-MinY);
    }
}
