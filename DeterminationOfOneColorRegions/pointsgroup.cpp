#include "pointsgroup.h"

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
    if (points.contains(QPair<int,int>(x,y)))
        return;
    if (points.size() > 0)
    {
        //averegeColour = (averegeColour * points.size() + pointColour) / (points.size() + 1);
        QRgb red = qRed(averageColour) * ((float)points.size() / (points.size() + 1)) + qRed(pointColour) / (points.size() + 1);
        QRgb green = qGreen(averageColour) * ((float)points.size() / (points.size() + 1)) + qGreen(pointColour) / (points.size() + 1);
        QRgb blue = qBlue(averageColour)  * ((float)points.size() / (points.size() + 1)) + qBlue(pointColour) / (points.size() + 1);
        averageColour = qRgb(red,green,blue);
    }
    else averageColour = pointColour;
    points.push_back(QPair<int,int>(x,y));
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
