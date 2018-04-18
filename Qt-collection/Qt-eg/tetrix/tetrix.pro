#-------------------------------------------------
#
# Project created by QtCreator 2017-12-02T19:49:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tetrix
TEMPLATE = app


SOURCES += main.cpp\
        tetrixwindow.cpp \
    tetrixpiece.cpp \
    tetrixboard.cpp

HEADERS  += tetrixwindow.h \
    tetrixboard.h \
    tetrixpiece.h

FORMS    += tetrixwindow.ui
