#-------------------------------------------------
#
# Project created by QtCreator 2016-03-11T17:21:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_opticonmonitor
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/opticonmonitor

include($$PWD/../../ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_opticonmonitor.cpp

HEADERS  += w_opticonmonitor.h
