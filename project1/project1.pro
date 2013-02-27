TEMPLATE = app
CONFIG += console
CONFIG -= qt

QMAKE_CXXFLAGS_DEBUG -= -O1 -O2 -O3
QMAKE_CXXFLAGS -= -O1 -O2 -O3

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
    -larmadillo
