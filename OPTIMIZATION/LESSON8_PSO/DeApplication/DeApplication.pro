TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        collection.cpp \
        demethod.cpp \
        gradientdescent.cpp \
        gradientwithls.cpp \
        main.cpp \
        problem.cpp \
        statistics.cpp

HEADERS += \
    collection.h \
    demethod.h \
    gradientdescent.h \
    gradientwithls.h \
    problem.h \
    statistics.h
