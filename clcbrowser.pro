#-------------------------------------------------
#
# Project created by QtCreator 2014-04-01T00:20:10
#
#-------------------------------------------------

QT       += core gui webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets webkitwidgets

TARGET = clcbrowser
TEMPLATE = app


SOURCES += main.cpp\
        clcwindow.cpp \
    clctab.cpp \
    settings.cpp \
    model.cpp \
    clcserver.cpp \
    cmd_parser.c \
    htmlhelp.cpp

HEADERS  += clcwindow.h \
    clctab.h \
    settings.h \
    singleton.h \
    model.h \
    clcserver.h \
    common.h \
    cmd_parser.h

CONFIG += c++11
