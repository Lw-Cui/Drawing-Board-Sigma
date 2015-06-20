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
#include <QDir>
#include <QPoint>
#include "plugininterface.h"
//#include "globalvar.h"

enum CurrentOp {
    drawing,
    moving
};

class pluginFactory : public QObject
{
    Q_OBJECT
public:
    pluginFactory();
    void loadPlugin(const QDir &pluginsDir);
    VisualObject *getPlugin(const QString &label);
    QVector<QPushButton *> getShapeButton();

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

    QVector<QPushButton *> getShapeButton();

signals:
    void sizeChanged(const QSize &);
    void redoAvailable(bool isAvailable);
    bool undoAvailable(bool isAvailable);

private slots:
    /*
    void setRect();
    void setCircle();
    void setScribble();
    void setStraight();
    void setTriangle();
    void setEllipse();
    */
    void setMoveShape();

    void receiveShapeChange(const QString & shape);

    void redo();
    void undo();

    void resizeCanvas(const QSize &size);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);

private:
    void SetDrawEntity(const QPoint &);
    void SetMoveEntity(const QPoint &point);

    void loadImage(const QString &fileName);
    void loadMyFormat(const QString &fileName);

    QImage canvas, backGround;
    QString currentShape;

    pluginFactory factory;

    QList <VisualObject*> AllShape;
    QList <VisualObject*> cacheShape;

    CurrentOp op;

    VisualObject* drawEntity;
    VisualArea* moveEntity;

    bool modified;
    QByteArray fileSuffix;
};

#endif // SCRIBBLEAREA_H
