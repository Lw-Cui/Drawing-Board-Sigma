#include <QtWidgets>
#include "circleplugin.h"

#define ID_LABEL "Circle"

Circle::Circle()
{
    identifyLabel = ID_LABEL;
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


CircleFactory::CircleFactory()
{
}

VisualObject *CircleFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new Circle;
    else
        return NULL;
}

QPushButton *CircleFactory::MyButton()
{
    QPushButton *drawCircleBut = new QPushButton;
    drawCircleBut->setIcon(QIcon(":/shape/circle"));
    connect(drawCircleBut, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawCircleBut;
}

void CircleFactory::changeShape()
{
       changeShapeCommand->execute(ID_LABEL);
}
