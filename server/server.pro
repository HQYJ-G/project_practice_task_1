#-------------------------------------------------
#
# Project created by QtCreator 2020-08-10T07:48:13
#
#-------------------------------------------------

QT       += core
QT       += network

QT       -= gui

LIBS    += -lsqlite3

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../sql/sqlite.cpp \
    handler.cpp \
    ../tcp/tcp.cpp

HEADERS += \
    ../sql/sqlite.h \
    ../protocol.h \
    handler.h \
    ../tcp/tcp.h
