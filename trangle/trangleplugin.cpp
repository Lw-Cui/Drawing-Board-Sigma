#include <QtWidgets>
#include "trangleplugin.h"

Triangle::Triangle()
{
    myShape = triangle;
}

bool Triangle::isDone()
{
    return points.size() == EDGE;
}

void VisualPolygon::drawTo(MouseStatus status, const QPoint &position)
{
    if (status == Release)
        points.append(position);
    else
        tempPosition = position;
}

void Triangle::paintWith(QPainter &painter)
{
    for (int i = 0; i < points.size() - 1; i++)
        painter.drawLine(points[i], points[i + 1]);

    if (points.size() == EDGE) {
        painter.drawLine(points[EDGE - 1], points[0]);
    } else if (points.size() == EDGE - 1) {
        painter.drawLine(points[points.size() - 1], tempPosition);
        painter.drawLine(points[0], tempPosition);
    } else {
        painter.drawLine(points[points.size() - 1], tempPosition);
    }
}


TriangleFactory::TriangleFactory()
{
    myShape = triangle;
}

VisualObject *TriangleFactory::create(CurrentShape thisShape)
{
    if (thisShape == myShape)
        return new Triangle;
    else
        return NULL;
}
