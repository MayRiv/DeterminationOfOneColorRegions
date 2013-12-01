#include "pointsgroup.h"
#include <QDebug>
PointsGroup::PointsGroup()
{
    averageColour = qRgb(0,0,0);
    pointsTest.push_back(new QVector<QPair<int,int> >());
}

QRgb PointsGroup::getGroupColour()
{
    return averageColour;
}

void PointsGroup::addPoint(int x, int y, QRgb pointColour)
{
    /*for(QVector<QVector<QPair<int,int> >* >::iterator groupIterator = pointsTest.begin(); groupIterator  != pointsTest.end(); groupIterator ++)
        if ((*groupIterator)->contains(QPair<int,int>(x,y))) return;
    TO DO.
    */
    QVector<QVector<QPair<int,int> >* >::iterator it = pointsTest.begin();
    while((*it)->size() > 64000)
    {
        if (++it == pointsTest.end())
        {
            pointsTest.push_back(new QVector<QPair<int,int> >());
            it=&pointsTest.last();
        }
    }
    unsigned long long int sum = 0;
    for(QVector<QVector<QPair<int,int> >* >::iterator groupIterator = pointsTest.begin(); groupIterator  != pointsTest.end(); groupIterator ++)
        sum += (*groupIterator)->size();

    QRgb red = qRed(averageColour) * ((float)sum / (sum + 1)) + (float)qRed(pointColour) / (sum + 1);
    QRgb green = qGreen(averageColour) * ((float)sum / (sum + 1)) + (float)qGreen(pointColour) / (sum + 1);
    QRgb blue = qBlue(averageColour)  * ((float)sum / (sum + 1)) + (float)qBlue(pointColour) / (sum + 1);
    averageColour = qRgb(red,green,blue);
    (*it)->push_back(QPair<int,int>(x,y));
}

bool PointsGroup::isDiffirent(QRgb value, int trashHold)
{
    //if (points.size() == 0) return false;
    if (pointsTest.first()->size() == 0) return false;
    if (abs(qRed(value) - qRed(averageColour)) > trashHold ||
        abs(qGreen(value) - qGreen(averageColour)) > trashHold ||
        abs(qBlue(value) - qBlue(averageColour)) > trashHold)
    {
        return true;
    }
    else return false;
}
