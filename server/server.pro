#-------------------------------------------------
#
# Project created by QtCreator 2020-08-08T17:10:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    ../sql/sqlite.cpp

HEADERS  += widget.h \
    ../sql/sqlite.h

FORMS    += widget.ui
