#-------------------------------------------------
#
# Project created by QtCreator 2016-03-14T12:53:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_stratagene
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/PCR/STRATAGENE

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)


SOURCES += main.cpp\
        w_stratagene.cpp

HEADERS  += w_stratagene.h
