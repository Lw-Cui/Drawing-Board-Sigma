#include <QtWidgets>
#include "scribblearea.h"
#include "plugininterface.h"

ScribbleArea::ScribbleArea()
{
    setScribble();
    resizeCanvas(QSize(470, 350));
    fileSuffix.append("pt");
    factory.loadPlugin(qApp->applicationDirPath());
    modified = false;
    setMouseTracking(true);
}

ScribbleArea::~ScribbleArea()
{
}

bool ScribbleArea::isModified()
{
    return modified;
}

void ScribbleArea::setModified(bool status)
{
    modified = status;
}

void ScribbleArea::loadFile(const QString &fileName)
{
    AllShape.clear();
    QFileInfo Info(fileName);
    if (Info.suffix() == fileSuffix)
        loadMyFormat(fileName);
    else
        loadImage(fileName);
}

void ScribbleArea::saveAsFile(const QString &fileName,
                              QByteArray format)
{
    canvas.save(fileName, format.constData());
}

void ScribbleArea::loadImage(const QString &fileName)
{
    backGround.load(fileName);
}

void ScribbleArea::loadMyFormat(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_4);

    quint32 label;
    in >> label;
    if (label != 0xA0B0C0D0)
        return;

    in >> canvas >> backGround;

    while (in.status() != QDataStream::ReadPastEnd) {
        int tmp;
        in >> tmp;
        VisualObject *obj = factory.getPlugin(static_cast<CurrentShape>(tmp));
        obj->readFromStram(in);
        AllShape.append(QPointer<VisualObject>(obj));
    }
    update();
}

void ScribbleArea::saveFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out << (quint32)0xA0B0C0D0;
    out.setVersion(QDataStream::Qt_5_4);

    out << canvas << backGround;
    foreach(QPointer<VisualObject> ite, AllShape) {
        out << static_cast<int>(ite->myShape);
        ite->writeToStream(out);
    }
}

const QByteArray &ScribbleArea::getSuffix()
{
    return fileSuffix;
}

const QSize ScribbleArea::getSize()
{
    return canvas.size();
}

void ScribbleArea::newDrawEntity(const QPoint &nowPosition)
{
    drawEntity = QPointer<VisualObject>(factory.getPlugin(shape));
    drawEntity->setDrawStart(nowPosition);
    emit undoAvailable(true);
}
/*
void ScribbleArea::findMoveEntity(const QPoint &point)
{
    moveEntity.clear();
    foreach(QPointer<VisualObject> ite, AllShape) {
        if (ite->isMoveable()) {
            moveEntity = dynamic_cast<VisualArea *>(ite.data());
            if (moveEntity->isContains(point)) {
                moveEntity->setMoveStart(point);
                AllShape.removeOne(ite);
                break;
            } else {
                moveEntity.clear();
            }
        }
    }
}
*/

void ScribbleArea::setRect()
{
    op = drawing;
    shape = rectangle;
    setCursor(Qt::CrossCursor);
}

void ScribbleArea::setCircle()
{
    op = drawing;
    shape = circle;
    setCursor(Qt::CrossCursor);
}

void ScribbleArea::setScribble()
{
    op = drawing;
    shape = scribble;
    setCursor(QCursor(QPixmap(":/cursor/scribble"), 10, 10));
}

void ScribbleArea::setStraight()
{
    op = drawing;
    shape = straight;
    setCursor(Qt::CrossCursor);
}

void ScribbleArea::setTriangle()
{
    op = drawing;
    shape = triangle;
    setCursor(Qt::CrossCursor);
}

void ScribbleArea::setEllipse()
{
    op = drawing;
    shape = ellipse;
    setCursor(Qt::CrossCursor);
}

void ScribbleArea::resizeCanvas(const QSize &size)
{
    QImage newImage(size, QImage::Format_ARGB32);
    newImage.fill(Qt::transparent);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), canvas);
    canvas = newImage;

    emit sizeChanged(size);
}

void ScribbleArea::redo()
{
    if (!cacheShape.isEmpty()) {
        AllShape.append(cacheShape.back());
        cacheShape.pop_back();
        emit undoAvailable(true);
        update();

        if (!cacheShape.isEmpty())
            emit redoAvailable(true);
        else
            emit redoAvailable(false);
    } else {
        emit redoAvailable(false);
    }
}

void ScribbleArea::undo()
{
    if (!AllShape.isEmpty()) {
        cacheShape.append(AllShape.back());
        AllShape.pop_back();
        emit redoAvailable(true);
        update();

        if (!AllShape.isEmpty())
            emit undoAvailable(true);
        else
            emit undoAvailable(false);
    } else {
        emit undoAvailable(false);
    }
}

void ScribbleArea::setMoveShape()
{
    op = moving;
    setCursor(Qt::SizeAllCursor);
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    switch (op) {
    case drawing:
        if (drawEntity.isNull())
            newDrawEntity(event->pos());
        break;
    case moving:
        //findMoveEntity(event->pos());
        break;
    default:
        break;
    }
    modified = true;
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    switch (op) {
    case drawing:
        if (!drawEntity.isNull()) {
            drawEntity->drawTo(Release, event->pos());
            update();
            if (drawEntity->isDone()) {
                AllShape.append(drawEntity);
                drawEntity.clear();
            }
        }
        break;
        /*
    case moving:
        if (!moveEntity.isNull()) {
            moveEntity->moveTo(event->pos());
            update();
            AllShape.append(dynamic_cast<VisualObject *>(moveEntity.data()));
            moveEntity.clear();
        }
        break;
        */
    default:
        break;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    switch (op) {
    case drawing:
        if (!drawEntity.isNull()) {
            drawEntity->drawTo(Move, event->pos());
            update();
        }
        break;
        /*
    case moving:
        if (!moveEntity.isNull()) {
            moveEntity->moveTo(event->pos());
            update();
        }
        break;
        */
    default:
        break;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *)
{
    canvas.fill(Qt::white);
    QPainter Painter(&canvas);
    Painter.drawImage(QPoint(0, 0), backGround);

    foreach(QPointer<VisualObject> ite, AllShape)
        ite->paintWith(Painter);
    if (!drawEntity.isNull())
        drawEntity->paintWith(Painter);
    /*
    if (!moveEntity.isNull())
        moveEntity->paintWith(Painter);
        */

    QPainter Paint(this);
    Paint.drawImage(QPoint(0, 0), canvas);
}

void pluginFactory::loadPlugin(const QString &path)
{
    QDir pluginsDir(path);
    pluginsDir.cdUp();
    pluginsDir.cd("plugDir");

    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
        pluginLoder.push_back(new QPluginLoader(pluginsDir.absoluteFilePath(fileName)));
}

VisualObject *pluginFactory::getPlugin(CurrentShape shape)
{
    foreach (QPluginLoader *loader, pluginLoder) {
        //VisualObject *ret = qobject_cast<VisualObject *>(loader->instance());
        QObject *p = loader->instance();
        VisualObject *ret = qobject_cast<VisualObject *>(p);
        if (ret && ret->myShape == shape)
            return ret;
    }
    return NULL;
}

pluginFactory::~pluginFactory()
{
    foreach (QPluginLoader *loader, pluginLoder)
        delete loader;
}
