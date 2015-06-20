#include <QtWidgets>
#include "visualline.h"
#define ID_LABEL "visualLine"

VisualLine::VisualLine()
    : drawingBoard(QSize(1000, 1000), QImage::Format_ARGB32)
{
    identifyLabel = ID_LABEL;
    drawingBoard.fill(Qt::transparent);
}

void VisualLine::setDrawStart(const QPoint &point)
{
    lastPoint = point;
}

void VisualLine::drawTo(MouseStatus, const QPoint &position)
{
    QPainter Painter(&drawingBoard);
    Painter.drawLine(lastPoint, position);
    lastPoint = position;
}

void VisualLine::paintWith(QPainter &painter)
{
    painter.drawImage(QPoint(0, 0), drawingBoard);
}


void VisualLine::writeToStream(QDataStream &out)
{
    out << drawingBoard;
}

void VisualLine::readFromStram(QDataStream &in)
{
    in >> drawingBoard;
}

bool VisualLine::isMoveable()
{
    return false;
}

bool VisualLine::isDone()
{
    return true;
}


VisualLineFactory::VisualLineFactory()
{
}

VisualObject *VisualLineFactory::create(const QString &thisLabel)
{
    if (thisLabel == ID_LABEL)
        return new VisualLine;
    else
        return NULL;
}

QPushButton *VisualLineFactory::MyButton()
{
    QPushButton *drawScribbleButton = new QPushButton;
    drawScribbleButton->setIcon(QIcon(":/shape/scribble"));
    connect(drawScribbleButton, SIGNAL(clicked()), this, SLOT(changeShape()));
    return drawScribbleButton;
}

void VisualLineFactory::changeShape()
{
    *point = ID_LABEL;
}
