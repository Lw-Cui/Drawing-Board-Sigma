#include "straight.h"

Straight::Straight()
{
    myShape = straight;
}


bool Straight::isContains(const QPoint &)
{
    return false;
}

void Straight::paintWith(QPainter &painter)
{
    painter.drawLine(startPoint, endPoint);
}


