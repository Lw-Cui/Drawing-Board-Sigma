#ifndef VISUALLINE
#define VISUALLINE

#include "plugininterface.h"

class VisualLine : //public VisualObject
        public QObject, VisualObject
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID VisualObject_iid)
    Q_INTERFACES(VisualObject)

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

#endif // VISUALLINE

