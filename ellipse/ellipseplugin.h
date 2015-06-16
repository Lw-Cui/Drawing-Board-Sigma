#ifndef ELLIPSEPLUGIN
#define ELLIPSEPLUGIN

#include "plugininterface.h"

class Ellipse : //public VisualShape
        public QObject, VisualShape
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualShape_iid)
    Q_INTERFACES(VisualShape)

public:
    Ellipse();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};


#endif // ELLIPSEPLUGIN

