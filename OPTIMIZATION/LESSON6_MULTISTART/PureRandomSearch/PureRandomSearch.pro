TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        problem.cpp \
        purerandomsearch.cpp \
        rastriginproblem.cpp \
        statistics.cpp

HEADERS += \
    problem.h \
    purerandomsearch.h \
    rastriginproblem.h \
    statistics.h
