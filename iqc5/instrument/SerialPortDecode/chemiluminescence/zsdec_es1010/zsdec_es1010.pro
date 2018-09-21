#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:50:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_es1010
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ES1010

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_es1010.cpp

HEADERS  += w_es1010.h
