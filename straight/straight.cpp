#include "straight.h"

#define ID_LABEL "straight"


Straight::Straight()
{
    identifyLabel = ID_LABEL;
}

bool Straight::isContains(const QPoint &)
{
    return false;
}

void Straight::paintWith(QPainter &painter)
{
    painter.drawLine(startPoint, endPoint);
}


StraightFactory::StraightFactory()
{
}

VisualObject *StraightFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new Straight;
    else
        return NULL;
}

QPushButton *StraightFactory::MyButton()
{
    QPushButton *drawStraightButton = new QPushButton;
    drawStraightButton->setIcon(QIcon(":/shape/straight"));
    connect(drawStraightButton, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawStraightButton;
}

void StraightFactory::changeShape()
{
    //currentShape = ID_LABEL;
}
