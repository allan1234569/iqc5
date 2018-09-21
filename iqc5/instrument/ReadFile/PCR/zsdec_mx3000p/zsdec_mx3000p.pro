#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T14:34:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_mx3000p
TEMPLATE = app
DESTDIR = $$PWD/../../../../bin/instr/PCR/mx3000p

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)


SOURCES += main.cpp\
        w_mx3000p.cpp

HEADERS  += w_mx3000p.h
