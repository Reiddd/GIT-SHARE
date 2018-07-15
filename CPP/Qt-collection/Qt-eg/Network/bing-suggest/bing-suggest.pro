#-------------------------------------------------
#
# Project created by QtCreator 2018-04-29T10:36:10
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bing-suggest
TEMPLATE = app


SOURCES += main.cpp\
        searchbox.cpp \
    bingsuggest.cpp

HEADERS  += searchbox.h \
    bingsuggest.h
