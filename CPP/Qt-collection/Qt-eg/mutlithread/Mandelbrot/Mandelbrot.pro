#-------------------------------------------------
#
# Project created by QtCreator 2018-04-21T21:18:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mandelbrot
TEMPLATE = app


SOURCES += main.cpp\
        mandelbrotwidget.cpp \
    renderthread.cpp

HEADERS  += mandelbrotwidget.h \
    renderthread.h
