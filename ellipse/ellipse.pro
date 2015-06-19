TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../drawingBoard
TARGET 		= ellipse
DESTDIR         = ../plugDir
HEADERS += \
SOURCES 	+= \
    ellipseplugin.h

SOURCES += \
    ellipseplugin.cpp

RESOURCES += \
    icon.qrc
