#ifndef VISUALOBJECT
#define VISUALOBJECT

#include <QWidget>
#include <QSize>
#include <QVector>
#include <QString>
#include <QImage>
#include <QPoint>
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

class VisualObject : public QObject
{
    Q_OBJECT
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
    void setMoveStart(const QPoint &point);

    bool isMoveable();

protected:
    QPoint moveStart;
    QPoint moveVector;
};

class VisualPolygon : public VisualArea
{
public:
    void setDrawStart(const QPoint &point);
    bool isContains(const QPoint &point);

    void moveTo(const QPoint &point);
    void drawTo(MouseStatus status, const QPoint &event);
    void paintWith(QPainter &painter);

    void writeToStream(QDataStream &out);
    void readFromStram(QDataStream &in);

protected:
    QVector<QPoint> points;
    QPoint tempPosition;
};

class Triangle : public VisualPolygon
{
public:
    Triangle();
    bool isDone();
    void paintWith(QPainter &painter);

private:
    const static int EDGE = 3;
};

class VisualLine : public VisualObject
{
public:
    VisualLine();
    void drawTo(MouseStatus, const QPoint &position);
    void paintWith(QPainter &painter);
    void setDrawStart(const QPoint &point);

    void writeToStream(QDataStream &out);
    void readFromStram(QDataStream &in);

    bool isMoveable();
    bool isDone();

private:
    QImage drawingBoard;
    QPoint lastPoint;
};

class VisualShape : public VisualArea
{
public:
    void setMoveStart(const QPoint &point);
    void setDrawStart(const QPoint &point);

    void moveTo(const QPoint &point);
    void drawTo(MouseStatus, const QPoint &position);

    void writeToStream(QDataStream &out);
    void readFromStram(QDataStream &in);

    bool isDone();

protected:
    QPoint startPoint;
    QPoint endPoint;
};

class Rect : public VisualShape
{
public:
    Rect();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class Circle : public VisualShape
{
public:
    Circle();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class Ellipse : public VisualShape
{
public:
    Ellipse();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class Straight : public VisualShape
{
public:
    Straight();

    bool isContains(const QPoint &);
    void paintWith(QPainter &painter);
};

#endif // VISUALOBJECT

