#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T16:18:02
#
#-------------------------------------------------

QT       += network core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP-server
TEMPLATE = app


SOURCES += main.cpp\
        server.cpp

HEADERS  += server.h

target.path = $$[QT_INSTALL_EXAMPLES]/network/fortunesever
INSTALLS += target
