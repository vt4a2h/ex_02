TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

CONFIG += c++11

QMAKE_CXXFLAGS += "-ofast"

HEADERS += \
    arrays.h

