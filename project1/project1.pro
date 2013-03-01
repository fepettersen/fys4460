TEMPLATE = app
CONFIG += console
CONFIG -= qt


QMAKE_CXXFLAGS_DEBUG -= -O1 -O2 -O3
QMAKE_CXXFLAGS -= -O1 -O2 -O3 -fopenmp

COMMON_CXXFLAGS = -std=c++0x -fopenmp
QMAKE_CXXFLAGS += $$COMMON_CXXFLAGS
QMAKE_CXXFLAGS_RELEASE += $$COMMON_CXXFLAGS
QMAKE_CXXFLAGS_DEBUG += $$COMMON_CXXFLAGS

SOURCES += main.cpp \
    particle.cpp \
    system.cpp \
    cell.cpp

HEADERS += \
    project1.h \
    particle.h \
    system.h \
    cell.h

LIBS += \
    -llapack \
    -lblas \
    -larmadillo\
    -fopenmp




