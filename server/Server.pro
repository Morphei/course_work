#-------------------------------------------------
#
# Project created by QtCreator 2014-12-03T21:33:21
#
#-------------------------------------------------

QT       += core gui network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app

LIBS += -L "/home/hkitty/Libs/SFML/build-SFML/lib"
#LIBS += -L"/home/morphei/libs/SFML-master-build/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += /home/hkitty/Libs/SFML/SFML-master/include
DEPENDPATH += /home/hkitty/Libs/SFML/SFML-master/include
#INCLUDEPATH += /home/morphei/libs/SFML-master/include
#DEPENDPATH += /home/morphei/libs/SFML-master/include

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
