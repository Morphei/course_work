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

LIBS += -L "/home/hkitty/Libs/SFML/build-SFML/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += /home/hkitty/Libs/SFML/SFML-master/include
DEPENDPATH += /home/hkitty/Libs/SFML/SFML-master/include

TEMPLATE = app


SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h

OTHER_FILES += \
    resources/grass_background.ora \
    resources/GoodDog.otf \
    resources/main_background.jpg \
    resources/main_background_800x600.jpg \
    resources/grass_background.jpg

