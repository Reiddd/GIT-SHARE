#-------------------------------------------------
#
# Project created by QtCreator 2018-04-28T16:15:03
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blocking-tcp-server
TEMPLATE = app


SOURCES += main.cpp\
        blockingclient.cpp \
    fortunethread.cpp

HEADERS  += blockingclient.h \
    fortunethread.h
