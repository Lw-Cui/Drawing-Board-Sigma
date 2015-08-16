#include <QtWidgets>
#include "scribblearea.h"
#include "plugininterface.h"

ScribbleArea::ScribbleArea()
    :drawEntity(NULL), moveEntity(NULL), modified(false)
{
    fileSuffix.append("pt");

    QDir path = qApp->applicationDirPath();
    path.cdUp();
    path.cd("plugDir");
    factory.loadPlugin(path);
    currentShape = "Circle";

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

    while (!in.atEnd()) {
        QString label;
        in >> label;
        VisualObject *obj = factory.getPlugin(label);
        obj->readFromStram(in);
        AllShape.append(obj);
    }
    update();
}

void ScribbleArea::saveFile(const QString &fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_5_4);
    out << (quint32)0xA0B0C0D0;

    out << canvas << backGround;
    foreach(VisualObject* ite, AllShape) {
        out << ite->identify();
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

QVector<QPushButton *> ScribbleArea::getShapeButton()
{
    return factory.getShapeButton(new ChangeShapeCommand(this));
}

void ScribbleArea::SetDrawEntity(const QPoint &nowPosition)
{
    drawEntity = factory.getPlugin(currentShape);
    drawEntity->setDrawStart(nowPosition);
    emit undoAvailable(true);
}

void ScribbleArea::SetMoveEntity(const QPoint &point)
{
    moveEntity = NULL;
    foreach(VisualObject* ite, AllShape) {
        if (ite->isMoveable()) {
            moveEntity = dynamic_cast<VisualArea *>(ite);
            if (moveEntity->isContains(point)) {
                moveEntity->setMoveStart(point);
                AllShape.removeOne(ite);
                break;
            } else {
                moveEntity = NULL;
            }
        }
    }
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

void ScribbleArea::ShapeChange(const QString &shape)
{
    op = drawing;
    currentShape = shape;
}


void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    switch (op) {
    case drawing:
        if (!drawEntity)
            SetDrawEntity(event->pos());
        break;
    case moving:
        SetMoveEntity(event->pos());
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
        if (drawEntity) {
            drawEntity->drawTo(Release, event->pos());
            update();
            if (drawEntity->isDone()) {
                AllShape.append(drawEntity);
                drawEntity = NULL;
            }
        }
        break;

    case moving:
        if (moveEntity) {
            moveEntity->moveTo(event->pos());
            update();
            AllShape.append(dynamic_cast<VisualObject *>(moveEntity));
            moveEntity = NULL;
        }
        break;

    default:
        break;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    switch (op) {
    case drawing:
        if (drawEntity) {
            drawEntity->drawTo(Move, event->pos());
            update();
        }
        break;

    case moving:
        if (moveEntity) {
            moveEntity->moveTo(event->pos());
            update();
        }
        break;

    default:
        break;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *)
{
    canvas.fill(Qt::white);
    QPainter Painter(&canvas);
    Painter.drawImage(QPoint(0, 0), backGround);

    foreach(VisualObject* ite, AllShape)
        ite->paintWith(Painter);
    if (drawEntity)
        drawEntity->paintWith(Painter);

    if (moveEntity)
        moveEntity->paintWith(Painter);

    QPainter Paint(this);
    Paint.drawImage(QPoint(0, 0), canvas);
}

pluginFactory::pluginFactory()
{
}

void pluginFactory::loadPlugin(const QDir &pluginsDir)
{
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
        pluginLoder.push_back(new QPluginLoader(pluginsDir.absoluteFilePath(fileName)));

}

VisualObject *pluginFactory::getPlugin(const QString &label)
{
    foreach (QPluginLoader *loader, pluginLoder) {
        ObjectFactory *q = qobject_cast<ObjectFactory *>(loader->instance());
        VisualObject *ret = q->create(label);
        if (ret)
            return ret;
    }
    return NULL;
}

QVector<QPushButton *> pluginFactory::getShapeButton(Command *p)
{
    QVector<QPushButton *>ret;
    foreach (QPluginLoader *loader, pluginLoder) {
        ObjectFactory *factory = qobject_cast<ObjectFactory *>(loader->instance());
        factory->setCommand(p);
        ret.push_back(factory->MyButton());
    }
    return ret;
}

pluginFactory::~pluginFactory()
{
    foreach (QPluginLoader *loader, pluginLoder)
        delete loader;
}


ChangeShapeCommand::ChangeShapeCommand(ScribbleArea *p)
    :application(p)
{
}

void ChangeShapeCommand::execute(const QString &shape)
{
    application->ShapeChange(shape);
}
