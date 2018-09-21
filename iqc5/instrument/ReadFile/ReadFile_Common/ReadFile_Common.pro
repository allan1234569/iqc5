#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T17:19:36
#
#-------------------------------------------------

QT       += core gui sql network axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReadFile_Common
TEMPLATE = app

include($$PWD/ReadFile_Common.pri)

SOURCES += main.cpp \
    widget.cpp

HEADERS  += \
    widget.h

FORMS    +=
