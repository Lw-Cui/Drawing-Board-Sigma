TEMPLATE        = lib
CONFIG         += plugin
QT             += widgets
INCLUDEPATH    += ../drawingBoard
TARGET 		= circle
DESTDIR         = ../plugDir
HEADERS += \
    circleplugin.h
SOURCES 	+= \
    circleplugin.cpp

RESOURCES += \
    icon.qrc
