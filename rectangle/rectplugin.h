#ifndef RECTPLUGIN
#define RECTPLUGIN

#include "plugininterface.h"

class Rect : public VisualShape
{
public:
    Rect();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class RectFactory : public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)

public:
    RectFactory();
    VisualObject *create(CurrentShape thisShape);
};

#endif // RECTPLUGIN

