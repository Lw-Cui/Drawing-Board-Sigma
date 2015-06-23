#ifndef ELLIPSEPLUGIN
#define ELLIPSEPLUGIN

#include "plugininterface.h"

class Ellipse : public VisualShape
{

public:
    Ellipse();

    bool isContains(const QPoint &point);
    void paintWith(QPainter &painter);
};

class EllipseFactory :
        public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)
public:
    EllipseFactory();
    VisualObject *create(const QString &thisLabel);

    QPushButton *MyButton();

private slots:
    void changeShape();
};

#endif // ELLIPSEPLUGIN

