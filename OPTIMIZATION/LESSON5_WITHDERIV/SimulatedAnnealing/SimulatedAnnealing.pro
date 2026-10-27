TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gradientdescent.cpp \
        gradientwithls.cpp \
        main.cpp \
        problem.cpp \
        rastriginproblem.cpp \
        simanmethod.cpp \
        statistics.cpp

HEADERS += \
    gradientdescent.h \
    gradientwithls.h \
    problem.h \
    rastriginproblem.h \
    simanmethod.h \
    statistics.h
