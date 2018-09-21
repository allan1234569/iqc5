#-------------------------------------------------
#
# Project created by QtCreator 2016-05-04T11:46:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_a2000
TEMPLATE = app


DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/A2000

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_a2000.cpp

HEADERS  += w_a2000.h
