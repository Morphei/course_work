#-------------------------------------------------
#
# Project created by QtCreator 2014-12-10T13:38:59
#
#-------------------------------------------------

QT       += core widgets

QT       -= gui

TARGET = server_sfml
CONFIG   += console
CONFIG   -= app_bundle

#LIBS += -L "/home/hkitty/Libs/SFML/build-SFML/lib"
LIBS += -L"/home/morphei/libs/SFML-master-build/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

#INCLUDEPATH += /home/hkitty/Libs/SFML/SFML-master/include
#DEPENDPATH += /home/hkitty/Libs/SFML/SFML-master/include
INCLUDEPATH += /home/morphei/libs/SFML-master/include
DEPENDPATH += /home/morphei/libs/SFML-master/include

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    mainwindow.cpp

HEADERS += \
    server.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

CONFIG +=c++11
