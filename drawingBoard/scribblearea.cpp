#include <QtWidgets>
#include "scribblearea.h"

ScribbleArea::ScribbleArea()
{
    setScribble();
    resizeCanvas(QSize(470, 350));
    fileSuffix.append("pt");
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

    int size;
    in >> size;

    while (size--) {
        int type;
        VisualObject *obj;
        in >> type;
        switch (type) {
        case 1:
            obj = new VisualLine;
            break;
        case 2:
            obj = new Circle;
            break;
        case 3:
            obj = new Rect;
            break;
        case 4:
            obj = new Ellipse;
            break;
        case 5:
            obj = new Straight;
            break;
        case 6:
            obj = new Triangle;
        default:
            break;
        }
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

    out << canvas << backGround << AllShape.size();
    foreach(QPointer<VisualObject> ite, AllShape) {
        switch (ite->myShape) {
        case scribble:
            out << 1;
            break;
        case circle:
            out << 2;
            break;
        case rectangle:
            out << 3;
            break;
        case ellipse:
            out << 4;
            break;
        case straight:
            out << 5;
            break;
        case triangle:
            out << 6;
        default:
            break;
        }
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
    VisualObject *obj;
    switch (shape) {
    case scribble:
        obj = new VisualLine;
        break;
    case circle:
        obj = new Circle;
        break;
    case rectangle:
        obj = new Rect;
        break;
    case ellipse:
        obj = new Ellipse;
        break;
    case straight:
        obj = new Straight;
        break;
    case triangle:
        obj = new Triangle;
        break;
    default:
        break;
    }

    drawEntity = QPointer<VisualObject>(obj);
    drawEntity->setDrawStart(nowPosition);
    emit undoAvailable(true);
}

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
        findMoveEntity(event->pos());
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
    case moving:
        if (!moveEntity.isNull()) {
            moveEntity->moveTo(event->pos());
            update();
            AllShape.append(dynamic_cast<VisualObject *>(moveEntity.data()));
            moveEntity.clear();
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
        if (!drawEntity.isNull()) {
            drawEntity->drawTo(Move, event->pos());
            update();
        }
        break;
    case moving:
        if (!moveEntity.isNull()) {
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

    foreach(QPointer<VisualObject> ite, AllShape)
        ite->paintWith(Painter);
    if (!drawEntity.isNull())
        drawEntity->paintWith(Painter);
    if (!moveEntity.isNull())
        moveEntity->paintWith(Painter);

    QPainter Paint(this);
    Paint.drawImage(QPoint(0, 0), canvas);
}
