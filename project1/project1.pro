TEMPLATE = app
CONFIG += console
CONFIG -= qt

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
