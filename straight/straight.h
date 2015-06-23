#ifndef STRAIGHT
#define STRAIGHT

#include "plugininterface.h"

class Straight : public VisualShape
{
public:
    Straight();
    bool isContains(const QPoint &);
    void paintWith(QPainter &painter);
};

class StraightFactory : public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)

public:
    StraightFactory();
    VisualObject *create(const QString &thisLabel);
    QPushButton *MyButton();

private slots:
    void changeShape();
};

#endif // STRAIGHT

