#-------------------------------------------------
#
# Project created by QtCreator 2016-10-05T11:19:11
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = multiplayer_snake
TEMPLATE = app

CONFIG+= c++11
SOURCES += main.cpp\
        mainwindow.cpp \
    snakeblock.cpp \
    snake.cpp \
    gamefield.cpp \
    snaketimer.cpp \
    food.cpp \
    connectdialog.cpp \
    socketthreadbase.cpp \
    server.cpp \
    client.cpp

HEADERS  += mainwindow.h \
    snakeblock.h \
    snake.h \
    gamefield.h \
    direction.h \
    snaketimer.h \
    food.h \
    connectdialog.h \
    socketthreadbase.h \
    server.h \
    client.h \
    commands.h

FORMS    += mainwindow.ui \
    connectdialog.ui
