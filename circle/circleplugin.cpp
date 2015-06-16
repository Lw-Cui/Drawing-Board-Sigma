#include <QtWidgets>
#include "circleplugin.h"

Circle::Circle()
{
    myShape = circle;
}

bool Circle::isContains(const QPoint &point)
{
    int diameter = endPoint.x() - startPoint.x();
    return QGraphicsEllipseItem(startPoint.x(), startPoint.y(),
                                diameter, diameter).contains(QPointF(point));
}

void Circle::paintWith(QPainter &painter)
{
    int diameter = endPoint.x() - startPoint.x();
    painter.drawEllipse(startPoint.x(), startPoint.y(),
                        diameter, diameter);
}
