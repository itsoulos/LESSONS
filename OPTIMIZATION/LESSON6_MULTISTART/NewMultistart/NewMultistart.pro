TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        collection.cpp \
        gradientdescent.cpp \
        gradientwithls.cpp \
        main.cpp \
        multistart.cpp \
        problem.cpp \
        statistics.cpp

HEADERS += \
    collection.h \
    gradientdescent.h \
    gradientwithls.h \
    multistart.h \
    problem.h \
    statistics.h
