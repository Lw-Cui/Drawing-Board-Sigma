#ifndef TRANGLE
#define TRANGLE

#include "plugininterface.h"

class Triangle : public QObject, VisualPolygon
{
    Q_OBJECT
    Q_INTERFACES(VisualPolygon)

public:
    Triangle();
    bool isDone();
    void paintWith(QPainter &painter);

private:
    const static int EDGE = 3;
};


#endif // TRANGLE

