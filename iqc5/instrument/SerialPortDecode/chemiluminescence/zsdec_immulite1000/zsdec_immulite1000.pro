#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T17:03:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_immulite1000
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/IMMULITE1000

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_immulite1000.cpp

HEADERS  += w_immulite1000.h
