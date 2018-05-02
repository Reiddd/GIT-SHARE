#-------------------------------------------------
#
# Project created by QtCreator 2018-05-01T12:12:18
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = chat-dialog
TEMPLATE = app


SOURCES += main.cpp\
        chatdialog.cpp \
    connection.cpp \
    server.cpp \
    client.cpp \
    peermanager.cpp

HEADERS  += chatdialog.h \
    connection.h \
    server.h \
    client.h \
    peermanager.h

FORMS += \
    chatdialog.ui
