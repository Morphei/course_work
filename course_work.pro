#-------------------------------------------------
#
# Project created by QtCreator 2014-11-29T20:27:43
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = course_work
CONFIG   += console
CONFIG   -= app_bundle

LIBS += -LD:\lib\SFML-2.1\lib

CONFIG(release, debug|release):LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release):LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:\lib\SFML-2.1\include
DEPENDPATH += D:\lib\SFML-2.1\include

TEMPLATE = app


SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h
