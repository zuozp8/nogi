#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T12:07:23
#
#-------------------------------------------------

QT       += core gui

QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = nogi
TEMPLATE = app


SOURCES += main.cpp\
        Visualiser.cpp \
    VisualiserCanvas.cpp \
    World.cpp \
    Robot.cpp \
    ParticleFilter.cpp

HEADERS  += Visualiser.hpp \
    VisualiserCanvas.hpp \
    World.hpp \
    Robot.hpp \
    ParticleFilter.hpp

FORMS    += Visualiser.ui
