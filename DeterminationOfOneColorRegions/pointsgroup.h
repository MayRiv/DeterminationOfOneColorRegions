#ifndef POINTSGROUP_H
#define POINTSGROUP_H
#include <QVector>
#include <QRgb>
#include <QPair>
class PointsGroup
{
public:
    PointsGroup();
    QRgb getGroupColour();
    void addPoint(int x,int y, QRgb pointColour);
    bool isDiffirent(QRgb value, int trashHold);
private:
    QVector<QPair<int,int> > points;
    QVector<QPair<int,int> > second;
    QVector<QVector<QPair<int,int> >* > pointsTest;
    QRgb averageColour;
};

#endif // POINTSGROUP_H
