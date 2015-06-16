#ifndef SCRIBBLEAREA_H
#define SCRIBBLEAREA_H

#include <QDataStream>
#include <QWidget>
#include <QSize>
#include <QObject>
#include <QList>
#include <QPointer>
#include <QString>
#include <QImage>
#include <QPluginLoader>
#include <QPoint>
#include "plugininterface.h"

enum CurrentOp {
    drawing,
    moving
};

class pluginFactory
{
public:
    void loadPlugin(const QString &path);
    VisualObject *getPlugin(enum CurrentShape shape);

    ~pluginFactory();
private:
    QVector<QPluginLoader *> pluginLoder;
};

class ScribbleArea : public QWidget
{
    Q_OBJECT
public:
    ScribbleArea();
    ~ScribbleArea();

    bool isModified();
    void setModified(bool status);

    void loadFile(const QString &fileName);
    void saveAsFile(const QString &fileName, QByteArray format);
    void saveFile(const QString &fileName);

    const QByteArray &getSuffix();

    const QSize getSize();

signals:
    void sizeChanged(const QSize &);
    void redoAvailable(bool isAvailable);
    bool undoAvailable(bool isAvailable);

private slots:
    void setRect();
    void setCircle();
    void setScribble();
    void setStraight();
    void setTriangle();
    void setEllipse();
    void setMoveShape();

    void redo();
    void undo();

    void resizeCanvas(const QSize &size);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void loadPlugin();

    void newDrawEntity(const QPoint &);
    //void findMoveEntity(const QPoint &point);

    void loadImage(const QString &fileName);
    void loadMyFormat(const QString &fileName);

    QImage canvas, backGround;

    pluginFactory factory;

    QList<QPointer<VisualObject> > AllShape;
    QList<QPointer<VisualObject> > cacheShape;

    CurrentOp op;
    CurrentShape shape;

    //QPointer<VisualArea> moveEntity;
    QPointer<VisualObject> drawEntity;

    bool modified;
    QByteArray fileSuffix;
};

#endif // SCRIBBLEAREA_H
