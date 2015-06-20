#include <QtWidgets>
#include "rectplugin.h"
#define ID_LABEL "rectangle"

Rect::Rect()
{
    identifyLabel = ID_LABEL;
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
}

VisualObject *RectFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new Rect;
    else
        return NULL;
}

QPushButton *RectFactory::MyButton()
{
    QPushButton *drawRectButton = new QPushButton;
    drawRectButton->setIcon(QIcon(":/shape/rect"));
    connect(drawRectButton, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawRectButton;
}

void RectFactory::changeShape()
{
    *point = ID_LABEL;
}
