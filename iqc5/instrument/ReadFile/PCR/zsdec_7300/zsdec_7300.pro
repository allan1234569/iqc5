#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T16:29:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_7300
TEMPLATE = app
DESTDIR = $$PWD/../../../../bin/instr/PCR/7300

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_7300.cpp

HEADERS  += w_7300.h
