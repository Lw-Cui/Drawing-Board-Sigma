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
    void resizeEvent(QResizeEvent *event);

signals:
    void resizeAll(const QSize);

private slots:
    void open();
    bool save();
    void addPlugin();

private:
    void createAction();
    void createButton();
    void createToolBar();
    void createMenu();
    void createDockWindow();
    void setLayout(QVBoxLayout *layout);

    void reloadPaintBox();
    bool questionAndSave();

    QString currentfileName;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *pluginMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QToolBar *pluginToolBar;

    QAction *undoAct;
    QAction *redoAct;
    QAction *openAct;
    QAction *saveAct;
    QAction *addPluginAct;

    QDockWidget *BoxDock;
    QVBoxLayout *shapeLayout;
    QVBoxLayout *toolLayout;
    QVBoxLayout *paintLayout;

    QGroupBox *paintBox;
    QGroupBox *toolBox;
    QGroupBox *shapeBox;


    QPushButton *moveBut;

    /*
    QPushButton *drawRectBut;
    QPushButton *drawCircleBut;
    QPushButton *ScribbleBut;
    QPushButton *drawEllipseBut;
    QPushButton *drawStraightBut;
    QPushButton *drawTriangleBut;
    */


    ScribbleArea *scribbleArea;

};

#endif // MAINWINDOW_H
