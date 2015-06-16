#ifndef RECTPLUGIN
#define RECTPLUGIN

#include "plugininterface.h"

class Rect : //public VisualShape
        public QObject, VisualShape
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualShape_iid)
    Q_INTERFACES(VisualShape)

public:
    Rect();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

#endif // RECTPLUGIN

