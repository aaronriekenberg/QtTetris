#-------------------------------------------------
#
# Project created by QtCreator 2013-06-08T06:07:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtTetris
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    tetrismodel.cpp \
    tetriscoordinate.cpp \
    squarepiece.cpp \
    tetrispiecefactory.cpp \
    tetrisstackcells.cpp \
    leftlpiece.cpp \
    rightlpiece.cpp \
    linepiece.cpp \
    tpiece.cpp \
    leftzpiece.cpp \
    rightzpiece.cpp

HEADERS  += mainwindow.h \
    tetrismodel.h \
    tetrisconstants.h \
    tetriscoordinate.h \
    tetrispiece.h \
    squarepiece.h \
    tetrispiecefactory.h \
    tetrisstackcells.h \
    leftlpiece.h \
    rightlpiece.h \
    linepiece.h \
    tpiece.h \
    leftzpiece.h \
    rightzpiece.h \
    abstracttetrispiece.h

FORMS    += mainwindow.ui
