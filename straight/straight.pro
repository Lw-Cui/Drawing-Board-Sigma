TEMPLATE = subdirs
TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../drawingBoard
TARGET 		= straight
DESTDIR         = ../plugDir
HEADERS 	+= \
    straight.cpp

HEADERS += \
    straight.h

