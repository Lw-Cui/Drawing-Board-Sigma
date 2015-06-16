#ifndef CIRCLEPLUGIN
#define CIRCLEPLUGIN

#include "plugininterface.h"

class Circle : //public VisualShape
        public QObject, VisualShape
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualShape_iid)
    Q_INTERFACES(VisualShape)

public:
    Circle();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

#endif // CIRCLEPLUGIN

