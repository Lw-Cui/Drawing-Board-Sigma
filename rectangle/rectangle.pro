TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../drawingBoard
TARGET 		= rectangle
DESTDIR         = ../plugDir
SOURCES 	+= \
    rectplugin.cpp
HEADERS += \
    rectplugin.h

RESOURCES += \
    icon.qrc
