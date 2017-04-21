#-------------------------------------------------
#
# Project created by QtCreator 2017-04-08T19:55:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Prac
TEMPLATE = app

CONFIG += c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    catalog.cpp \
    radioprogram.cpp \
    statistics.cpp \
    requestsgenerator.cpp \
    simulator.cpp \
    royalmanager.cpp \
    events.cpp \
    structures.cpp \
    timetableeditorform.cpp \
    genrediscriber.cpp \
    authordescriber.cpp \
    albumdescriber.cpp \
    songdescriber.cpp

HEADERS  += mainwindow.h \
    structures.h \
    catalog.h \
    radioprogram.h \
    statistics.h \
    requestsgenerator.h \
    types.h \
    simulator.h \
    events.h \
    royalmanager.h \
    timetableeditorform.h \
    genrediscriber.h \
    authordescriber.h \
    albumdescriber.h \
    songdescriber.h

FORMS    += mainwindow.ui \
    timetableeditorform.ui \
    genrediscriber.ui \
    authordescriber.ui \
    albumdescriber.ui \
    songdescriber.ui

DISTFILES += \
    Prac.pro.user \
    CMakeLists.txt
