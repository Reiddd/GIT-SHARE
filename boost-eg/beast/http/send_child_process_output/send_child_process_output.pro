TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

_BOOST_PATH  = /usr/local/Cellar/boost/1.67.0_1
INCLUDEPATH +=   $${_BOOST_PATH}/include/
LIBS        += -L$${_BOOST_PATH}/lib
LIBS        += -lboost_system

SOURCES += main.cpp
