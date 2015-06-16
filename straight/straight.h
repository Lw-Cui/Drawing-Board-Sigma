#ifndef STRAIGHT
#define STRAIGHT

#include "plugininterface.h"

class Straight : //public VisualShape
        public QObject, VisualShape
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualShape_iid)
    Q_INTERFACES(VisualShape)

public:
    Straight();

    bool isContains(const QPoint &);
    void paintWith(QPainter &painter);
};

#endif // STRAIGHT

