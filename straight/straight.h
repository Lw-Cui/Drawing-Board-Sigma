#ifndef STRAIGHT
#define STRAIGHT

#include "plugininterface.h"

class Straight : public QObject, VisualShape
{
    Q_OBJECT
    Q_INTERFACES(VisualShape)

public:
    Straight();

    bool isContains(const QPoint &);
    void paintWith(QPainter &painter);
};

#endif // STRAIGHT

