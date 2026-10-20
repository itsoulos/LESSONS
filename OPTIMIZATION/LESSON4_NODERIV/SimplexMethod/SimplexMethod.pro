TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        problem.cpp \
        rastriginproblem.cpp \
        simplexmethod.cpp

HEADERS += \
    problem.h \
    rastriginproblem.h \
    simplexmethod.h
