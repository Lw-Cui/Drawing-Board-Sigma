TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../drawingBoard
TARGET 		= visualLine
DESTDIR         = ../plugDir
SOURCES 	+= \
    visualline.cpp

HEADERS += \
    visualline.h
