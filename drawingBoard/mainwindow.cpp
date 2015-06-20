#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    resize(scribbleArea->getSize().width() + 100,
           scribbleArea->getSize().height() + 100);

    createAction();
    createButton();
    createMenu();
    createToolBar();
    createDockWindow();
}

MainWindow::~MainWindow()
{

}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (questionAndSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::createMenu()
{
    fileMenu = menuBar()->addMenu(tr("&file"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&edit"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
}

void MainWindow::createDockWindow()
{
    /*
    QGridLayout *shapeLayout = new QGridLayout;
    shapeLayout->addWidget(drawRectBut, 0, 0);
    shapeLayout->addWidget(drawEllipseBut, 1, 0);
    shapeLayout->addWidget(drawCircleBut, 2, 0);
    shapeLayout->addWidget(drawStraightBut, 3, 0);
    shapeLayout->addWidget(drawTriangleBut, 4, 0);
    shapeLayout->addWidget(ScribbleBut, 5, 0);
    shapeLayout->addWidget(moveBut, 6, 0);
    */

    QVBoxLayout *shapeLayout = new QVBoxLayout;
    QVector <QPushButton *> allButton = scribbleArea->getShapeButton();
    foreach(QPushButton *button, allButton)
        shapeLayout->addWidget(button);

    shape = new QGroupBox(tr("paint"));
    setLayout(shapeLayout);
    shape->setLayout(shapeLayout);

    QVBoxLayout *toolLayout = new QVBoxLayout;
    setLayout(toolLayout);
    toolLayout->addWidget(moveBut);

    tool = new QGroupBox(tr("tool"));
    tool->setLayout(toolLayout);

    QVBoxLayout *paintLayout = new QVBoxLayout;
    paintLayout->addWidget(shape);
    paintLayout->addWidget(tool);
    setLayout(paintLayout);

    paintBox = new QGroupBox;
    paintBox->setLayout(paintLayout);

    BoxDock = new QDockWidget(tr("Box"));
    BoxDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, BoxDock);

    BoxDock->setWidget(paintBox);
}


void MainWindow::setLayout(QVBoxLayout *layout)
{
    layout->setAlignment(Qt::AlignTop);
    layout->setSpacing(0);
    layout->setContentsMargins(5, 8, 0, 8);
}

bool MainWindow::questionAndSave()
{
    if (scribbleArea->isModified()) {
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, tr("painter"),
                                   tr("The image has been modified.\n"
                                      "Do you want to save your changes?"),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
        else
            return true;
    } else {
        return true;
    }
}

void MainWindow::createAction()
{
    openAct = new QAction(QIcon(":/action/open"), tr("&open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    undoAct = new QAction(QIcon(":/action/undo"), tr("&undo"), this);
    undoAct->setShortcut(QKeySequence::Undo);
    connect(undoAct, SIGNAL(triggered()), scribbleArea, SLOT(undo()));
    connect(scribbleArea, SIGNAL(undoAvailable(bool)), undoAct, SLOT(setEnabled(bool)));
    undoAct->setEnabled(false);

    redoAct = new QAction(QIcon(":/action/redo"), tr("&redo"), this);
    redoAct->setShortcut(QKeySequence::Redo);
    connect(redoAct, SIGNAL(triggered()), scribbleArea, SLOT(redo()));
    connect(scribbleArea, SIGNAL(redoAvailable(bool)), redoAct, SLOT(setEnabled(bool)));
    redoAct->setEnabled(false);

    saveAct = new QAction(QIcon(":/action/save"), tr("&save"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));
}

void MainWindow::createButton()
{
    /*
    drawRectBut = new QPushButton;
    drawRectBut->setIcon(QIcon(":/shape/rect"));
    connect(drawRectBut, SIGNAL(clicked()), scribbleArea, SLOT(setRect()));

    drawRectBut->setAutoExclusive(true);

    drawEllipseBut = new QPushButton;
    drawEllipseBut->setIcon(QIcon(":/shape/ellipse"));
    connect(drawEllipseBut, SIGNAL(clicked()), scribbleArea, SLOT(setEllipse()));

    drawCircleBut = new QPushButton;
    drawCircleBut->setIcon(QIcon(":/shape/circle"));
    connect(drawCircleBut, SIGNAL(clicked()), scribbleArea, SLOT(setCircle()));

    drawStraightBut = new QPushButton;
    drawStraightBut->setIcon(QIcon(":/shape/straight"));
    connect(drawStraightBut, SIGNAL(clicked()), scribbleArea, SLOT(setStraight()));

    ScribbleBut = new QPushButton;
    ScribbleBut->setIcon(QIcon(":/shape/scribble"));
    connect(ScribbleBut, SIGNAL(clicked()), scribbleArea, SLOT(setScribble()));

    drawTriangleBut = new QPushButton;
    drawTriangleBut->setIcon(QIcon(":/shape/triangle"));
    connect(drawTriangleBut, SIGNAL(clicked()), scribbleArea, SLOT(setTriangle()));
    */

    moveBut = new QPushButton;
    moveBut->setIcon(QIcon(":/cursor/move"));
    connect(moveBut, SIGNAL(clicked()), scribbleArea, SLOT(setMoveShape()));

    moveBut->setAutoExclusive(true);
}

void MainWindow::createToolBar()
{
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(openAct);
    fileToolBar->addAction(saveAct);
    fileToolBar->setIconSize(QSize(17, 17));

    editToolBar = addToolBar(tr("edit"));
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->setIconSize(QSize(17, 17));
}

void MainWindow::open()
{
    if (questionAndSave()) {
        currentfileName = QFileDialog::getOpenFileName(this, tr("open file"));
        if (!currentfileName.isEmpty())
            scribbleArea->loadFile(currentfileName);
    }

    resize(scribbleArea->getSize().width() + 100,
           scribbleArea->getSize().height() + 100);
}

bool MainWindow::save()
{
    if (currentfileName.isEmpty()) {
        QString initialPath = QDir::currentPath()
                + "/untitle." + scribbleArea->getSuffix();
        currentfileName = QFileDialog::getSaveFileName(this,
               tr("Save"), initialPath,
               tr("Painter Files(*.%1)")
                 .arg(scribbleArea->getSuffix().constData()));
        if (currentfileName.isEmpty())
        return false;
    }
    if (scribbleArea->isModified()) {
        scribbleArea->saveFile(currentfileName);
        scribbleArea->setModified(false);
    }
    return true;
}
