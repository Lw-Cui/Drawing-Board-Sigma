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


RectFactory::RectFactory()
{
    myShape = rectangle;
}

VisualObject *RectFactory::create(CurrentShape thisShape)
{
    if (thisShape == myShape)
        return new Rect;
    else
        return NULL;
}
