TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        collection.cpp \
        gradientdescent.cpp \
        gradientwithls.cpp \
        main.cpp \
        problem.cpp \
        psomethod.cpp \
        statistics.cpp

HEADERS += \
    collection.h \
    gradientdescent.h \
    gradientwithls.h \
    problem.h \
    psomethod.h \
    statistics.h
