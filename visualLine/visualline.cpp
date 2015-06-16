#include <QtWidgets>
#include "visualline.h"

VisualLine::VisualLine()
    : drawingBoard(QSize(1000, 1000), QImage::Format_ARGB32)
{
    drawingBoard.fill(Qt::transparent);
    myShape = scribble;
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
