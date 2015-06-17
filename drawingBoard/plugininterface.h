#ifndef PLUGININTERFACE
#define PLUGININTERFACE

#include <QWidget>
#include <QSize>
#include <QVector>
#include <QString>
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QDataStream>

enum CurrentShape{
    scribble,
    rectangle,
    circle,
    ellipse,
    straight,
    triangle
};

enum MouseStatus {
    Press,
    Move,
    Release
};

class VisualObject
{
public:
    virtual void setDrawStart(const QPoint &point) = 0;

    virtual void drawTo(MouseStatus status, const QPoint &event) = 0;
    virtual void paintWith(QPainter &painter) = 0;

    virtual void writeToStream(QDataStream &out) = 0;
    virtual void readFromStram(QDataStream &in) = 0;

    virtual bool isMoveable() = 0;
    virtual bool isDone() = 0;

    CurrentShape myShape;
};

class VisualArea : public VisualObject
{
public:
    virtual void moveTo(const QPoint &point) = 0;
    virtual bool isContains(const QPoint &point) = 0;
    void setMoveStart(const QPoint &point) {
        moveStart = point;
    }

    bool isMoveable() {
        return true;
    }

protected:
    QPoint moveStart;
    QPoint moveVector;
};

class VisualShape : public VisualArea
{
public:
    void setMoveStart(const QPoint &point);
    void setDrawStart(const QPoint &point) {
        startPoint = point;
    }

    void moveTo(const QPoint &point) {
        moveVector = point - moveStart;
        startPoint += moveVector;
        endPoint += moveVector;
        moveStart = point;
    }

    void drawTo(MouseStatus, const QPoint &position) {
        endPoint = position;
    }

    void writeToStream(QDataStream &out) {
        out << startPoint << endPoint;
    }

    void readFromStram(QDataStream &in) {
        in >> startPoint >> endPoint;
    }

    bool isDone() {
        return true;
    }

protected:
    QPoint startPoint;
    QPoint endPoint;
};

class VisualPolygon : public VisualArea
{
public:
    void setDrawStart(const QPoint &point) {
        points.push_back(point);
    }

    bool isContains(const QPoint &point) {
        return QPolygon(points).containsPoint(point, Qt::OddEvenFill);
    }

    void moveTo(const QPoint &point) {
        moveVector = point - moveStart;
        for (int i = 0; i < points.size(); i++)
            points[i] += moveVector;
        moveStart = point;
    }

    void drawTo(MouseStatus status, const QPoint &event);
    void paintWith(QPainter &painter) {
        painter.drawPolygon(QPolygon(points));
    }

    void writeToStream(QDataStream &out) {
        out << points.size();
        for (int i = 0; i < points.size(); i++)
            out << points.at(i);
    }

    void readFromStram(QDataStream &in) {
        int size;
        in >> size;
        points.resize(size);

        for (int i = 0; i < points.size(); i++)
            in >> points[i];
    }

protected:
    QVector<QPoint> points;
    QPoint tempPosition;
};

class ObjectFactory
{
public:
    virtual VisualObject* create(CurrentShape thisShape) = 0;

protected:
    CurrentShape myShape;
};

#define VisualObjectFactory_iid "drawingBoard.plugin.VisualObject"
Q_DECLARE_INTERFACE(ObjectFactory, VisualObjectFactory_iid)

#endif // PLUGININTERFACE

