#include "pointsgroup.h"
#include <QDebug>
PointsGroup::PointsGroup()
{
    averageColour = qRgb(0,0,0);
}

QRgb PointsGroup::getGroupColour()
{
    return averageColour;
}

void PointsGroup::addPoint(int x, int y, QRgb pointColour)
{
    if (points.contains(QPair<int,int>(x,y)) || second.contains(QPair<int,int>(x,y)))
        return;
    if (points.size() > 0)
    {
        int firstSize  = points.size();
        int secondSize = second.size();
        //int thirdSize  = third.size();
        //int foursSize  = fours.size();
        unsigned long int sum = firstSize + secondSize ;//+ thirdSize + foursSize;
        QRgb red = qRed(averageColour) * ((float)sum / (sum + 1)) + (float)qRed(pointColour) / (sum + 1);
        QRgb green = qGreen(averageColour) * ((float)sum / (sum + 1)) + (float)qGreen(pointColour) / (sum + 1);
        QRgb blue = qBlue(averageColour)  * ((float)sum / (sum + 1)) + (float)qBlue(pointColour) / (sum + 1);
        averageColour = qRgb(red,green,blue);
    }
    else averageColour = pointColour;
    if (points.size() < 62000) points.push_back(QPair<int,int>(x,y));
    /*else
    if (second.size() < 62000) second.push_back(QPair<int,int>(x,y));
    else
    if (third.size()  < 62000) third.push_back(QPair<int,int>(x,y));
    else
    if (third.size()  < 62000) fours.push_back(QPair<int,int>(x,y));
    else
    {
        qDebug() << "Jopa";
    }*/
}

bool PointsGroup::isDiffirent(QRgb value, int trashHold)
{
    if (points.size() == 0) return false;

    if (abs(qRed(value) - qRed(averageColour)) > trashHold ||
        abs(qGreen(value) - qGreen(averageColour)) > trashHold ||
        abs(qBlue(value) - qBlue(averageColour)) > trashHold)
    {
        return true;
    }
    else return false;
}
