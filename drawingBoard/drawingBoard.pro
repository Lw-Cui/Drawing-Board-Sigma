#-------------------------------------------------
#
# Project created by QtCreator 2015-06-15T08:35:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = drawingBoard
TEMPLATE = app


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    scribblearea.cpp \
    globalvar.cpp

HEADERS  += \
    mainwindow.h \
    scribblearea.h \
    plugininterface.h \
    globalvar.h

RESOURCES += \
    image.qrc
