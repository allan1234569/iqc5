#-------------------------------------------------
#
# Project created by QtCreator 2016-03-16T12:33:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_lightcycle
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/lightcycle

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp \
    w_lightcycler.cpp

HEADERS  += \
    w_lightcycler.h
