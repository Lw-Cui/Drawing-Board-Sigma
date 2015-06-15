#include <QtWidgets>
#include "visualobject.h"

void VisualArea::setMoveStart(const QPoint &point)
{
    moveStart = point;
}

bool VisualArea::isMoveable()
{
    return true;
}

void VisualShape::setDrawStart(const QPoint &point)
{
    startPoint = point;
}

void VisualShape::moveTo(const QPoint &point)
{
    moveVector = point - moveStart;
    startPoint += moveVector;
    endPoint += moveVector;
    moveStart = point;
}

void VisualShape::drawTo(MouseStatus, const QPoint &position)
{
    endPoint = position;
}

void VisualShape::writeToStream(QDataStream &out)
{
    out << startPoint << endPoint;
}

void VisualShape::readFromStram(QDataStream &in)
{
    in >> startPoint >> endPoint;
}

bool VisualShape::isDone()
{
    return true;
}

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

bool VisualPolygon::isContains(const QPoint &point)
{
    return QPolygon(points).containsPoint(point, Qt::OddEvenFill);

}

void VisualPolygon::moveTo(const QPoint &point)
{
    moveVector = point - moveStart;
    for (int i = 0; i < points.size(); i++)
        points[i] += moveVector;
    moveStart = point;
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

Ellipse::Ellipse()
{
    myShape = ellipse;
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


Straight::Straight()
{
    myShape = straight;
}


bool Straight::isContains(const QPoint &)
{
    return false;
}

void Straight::paintWith(QPainter &painter)
{
    painter.drawLine(startPoint, endPoint);
}

void VisualPolygon::setDrawStart(const QPoint &point)
{
    points.push_back(point);
}

void VisualPolygon::paintWith(QPainter &painter)
{
    painter.drawPolygon(QPolygon(points));
}

void VisualPolygon::writeToStream(QDataStream &out)
{
    out << points.size();
    for (int i = 0; i < points.size(); i++)
        out << points.at(i);
}

void VisualPolygon::readFromStram(QDataStream &in)
{
    int size;
    in >> size;
    points.resize(size);

    for (int i = 0; i < points.size(); i++)
        in >> points[i];
}

Triangle::Triangle()
{
    myShape = triangle;
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
