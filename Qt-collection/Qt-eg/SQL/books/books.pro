#-------------------------------------------------
#
# Project created by QtCreator 2018-05-05T12:47:55
#
#-------------------------------------------------

QT       += sql core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = books
TEMPLATE = app


SOURCES += main.cpp\
        bookwindow.cpp \
    bookdelegate.cpp

HEADERS  += bookwindow.h \
    bookdelegate.h \
    initdb.h

FORMS += \
    bookwindow.ui

DISTFILES +=

RESOURCES += \
    books.qrc
