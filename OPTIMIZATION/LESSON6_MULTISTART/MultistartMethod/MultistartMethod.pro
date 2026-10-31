TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        gradientdescent.cpp \
        gradientwithls.cpp \
        main.cpp \
        multistart.cpp \
        problem.cpp \
        rastriginproblem.cpp \
        statistics.cpp

HEADERS += \
    gradientdescent.h \
    gradientwithls.h \
    multistart.h \
    problem.h \
    rastriginproblem.h \
    statistics.h
