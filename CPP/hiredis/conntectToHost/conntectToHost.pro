TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

_HIREDIS_PATH = /usr/local/Cellar/hiredis/0.13.3
INCLUDEPATH  += $${_HIREDIS_PATH}/include/
LIBS         += -L$${_HIREDIS_PATH}/lib
LIBS         += -lhiredis

SOURCES += main.cpp
