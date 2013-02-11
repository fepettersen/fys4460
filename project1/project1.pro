TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    particle.cpp \
    system.cpp \
    integrator_md.cpp

HEADERS += \
    project1.h \
    particle.h \
    system.h \
    integrator_md.h

LIBS += \
    -llapack \
    -lblas \
    -larmadillo
