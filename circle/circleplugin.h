#ifndef CIRCLEPLUGIN
#define CIRCLEPLUGIN

#include "plugininterface.h"

class Circle : public QObject, VisualShape
{
    Q_OBJECT
    Q_INTERFACES(VisualShape)

public:
    Circle();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

#endif // CIRCLEPLUGIN

