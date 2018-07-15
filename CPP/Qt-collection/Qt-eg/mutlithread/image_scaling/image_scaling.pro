#-------------------------------------------------
#
# Project created by QtCreator 2018-04-22T18:29:54
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_scaling
TEMPLATE = app


SOURCES += main.cpp\
        images.cpp

HEADERS  += images.h

target.path = $$[QT_INSTALL_EXAMPLES]/qtconcurrent/imagescaling
INSTALLS += target
