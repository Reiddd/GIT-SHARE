#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T16:40:49
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = http-download-client
TEMPLATE = app


SOURCES += main.cpp\
        httpwindow.cpp

HEADERS  += httpwindow.h

FORMS    += \
    authenticationdialog.ui
