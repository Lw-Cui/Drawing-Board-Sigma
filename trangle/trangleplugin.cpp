#include <QtWidgets>
#include "trangleplugin.h"
#define ID_LABEL "triangle"

Triangle::Triangle()
{
    identifyLabel = ID_LABEL;
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
}

VisualObject *TriangleFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new Triangle;
    else
        return NULL;
}

QPushButton *TriangleFactory::MyButton()
{
    QPushButton *drawTriangleButton = new QPushButton;
    drawTriangleButton->setIcon(QIcon(":/shape/triangle"));
    connect(drawTriangleButton, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawTriangleButton;
}

void TriangleFactory::changeShape()
{
    *point = ID_LABEL;
}
