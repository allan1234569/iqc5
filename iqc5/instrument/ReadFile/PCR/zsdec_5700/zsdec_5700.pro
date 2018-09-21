#-------------------------------------------------
#
# Project created by QtCreator 2016-02-26T17:22:10
#
#-------------------------------------------------

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_5700
TEMPLATE = app
DESTDIR = $$PWD/../../../../bin/instr/PCR/5700

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_5700.cpp

HEADERS  += w_5700.h
