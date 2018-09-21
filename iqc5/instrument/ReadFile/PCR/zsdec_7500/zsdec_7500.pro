#-------------------------------------------------
#
# Project created by QtCreator 2016-03-07T15:30:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_7500
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/7500

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_7500.cpp

HEADERS  += w_7500.h

FORMS    +=
