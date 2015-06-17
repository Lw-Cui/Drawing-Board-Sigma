#ifndef CIRCLEPLUGIN
#define CIRCLEPLUGIN

#include "plugininterface.h"

class Circle : public VisualShape
{
public:
    Circle();
    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class CircleFactory :
        public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)
public:
    CircleFactory();
    VisualObject *create(CurrentShape thisShape);
};

#endif // CIRCLEPLUGIN

