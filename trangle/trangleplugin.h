#ifndef TRANGLE
#define TRANGLE

#include "plugininterface.h"

class Triangle : //public VisualPolygon
        public QObject, VisualPolygon
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualPolygon_iid)
    Q_INTERFACES(VisualPolygon)

public:
    Triangle();
    bool isDone();
    void paintWith(QPainter &painter);

private:
    const static int EDGE = 3;
};


#endif // TRANGLE

