#ifndef TRANGLE
#define TRANGLE

#include "plugininterface.h"

class Triangle : public VisualPolygon
{
public:
    Triangle();
    bool isDone();
    void paintWith(QPainter &painter);

private:
    const static int EDGE = 3;
};

class TriangleFactory :
        public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)
public:
    TriangleFactory();
    VisualObject *create(const QString &thisLabel);
    QPushButton *MyButton();

private slots:
    void changeShape();
};


#endif // TRANGLE

