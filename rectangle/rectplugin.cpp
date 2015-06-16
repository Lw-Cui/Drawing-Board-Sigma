#include <QtWidgets>
#include "rectplugin.h"

Rect::Rect()
{
    myShape = rectangle;
}

bool Rect::isContains(const QPoint &point)
{
    return QGraphicsRectItem(QRect(startPoint, endPoint))
            .contains(QPointF(point));
}

void Rect::paintWith(QPainter &painter)
{
    painter.drawRect(QRect(startPoint, endPoint));
}
