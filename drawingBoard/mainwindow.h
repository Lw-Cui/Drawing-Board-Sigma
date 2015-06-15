#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QMenu>
#include "scribblearea.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void open();
    bool save();

private:
    void createAction();
    void createButton();
    void createToolBar();
    void createMenu();
    void createDockWindow();
    void setLayout(QGridLayout *layout);

    bool questionAndSave();

    QString currentfileName;

    QMenu *fileMenu;
    QMenu *editMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *undoAct;
    QAction *redoAct;
    QAction *openAct;
    QAction *saveAct;

    QDockWidget *BoxDock;

    QGroupBox *paintBox;

    QGroupBox *shape;
    QPushButton *drawRectBut;
    QPushButton *drawCircleBut;
    QPushButton *ScribbleBut;
    QPushButton *drawEllipseBut;
    QPushButton *drawStraightBut;
    QPushButton *drawTriangleBut;

    QGroupBox *tool;
    QPushButton *moveBut;

    ScribbleArea *scribbleArea;

};

#endif // MAINWINDOW_H
