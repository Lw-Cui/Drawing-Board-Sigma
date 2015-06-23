#include <QtWidgets>
#include "ellipseplugin.h"
#define ID_LABEL "ellipse"

Ellipse::Ellipse()
{
    identifyLabel = ID_LABEL;
}

bool Ellipse::isContains(const QPoint &point)
{
    return QGraphicsEllipseItem(startPoint.x(), startPoint.y(),
                                endPoint.x() - startPoint.x(),
                                endPoint.y() - startPoint.y()).contains(QPointF(point));
}

void Ellipse::paintWith(QPainter &painter)
{
   painter.drawEllipse(startPoint.x(), startPoint.y(),
                                endPoint.x() - startPoint.x(),
                                endPoint.y() - startPoint.y());
}




EllipseFactory::EllipseFactory()
{
}

VisualObject *EllipseFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new Ellipse;
    else
        return NULL;
}

QPushButton *EllipseFactory::MyButton()
{
    QPushButton *drawEllipseBut = new QPushButton;
    drawEllipseBut->setIcon(QIcon(":/shape/ellipse"));
    connect(drawEllipseBut, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawEllipseBut;
}

void EllipseFactory::changeShape()
{
    changeShapeCommand->execute(ID_LABEL);
}
