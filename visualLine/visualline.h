#ifndef VISUALLINE
#define VISUALLINE

#include "plugininterface.h"

class VisualLine : public VisualObject
{
public:
    VisualLine();
    void drawTo(MouseStatus, const QPoint &position);
    void paintWith(QPainter &painter);
    void setDrawStart(const QPoint &point);

    void writeToStream(QDataStream &out);
    void readFromStram(QDataStream &in);

    bool isMoveable();
    bool isDone();

private:
    QImage drawingBoard;
    QPoint lastPoint;
};

class VisualLineFactory :
        public QObject, ObjectFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObjectFactory_iid)
    Q_INTERFACES(ObjectFactory)
public:
    VisualLineFactory();
    VisualObject *create(CurrentShape thisShape);
};

#endif // VISUALLINE

