#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T11:24:22
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_fluocycle
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/fluocycle

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_fluocycle.cpp

HEADERS  += w_fluocycle.h
