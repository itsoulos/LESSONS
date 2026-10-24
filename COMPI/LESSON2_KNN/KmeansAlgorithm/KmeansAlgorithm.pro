TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        dataset.cpp \
        kmeans.cpp \
        main.cpp

HEADERS += \
    dataset.h \
    kmeans.h
