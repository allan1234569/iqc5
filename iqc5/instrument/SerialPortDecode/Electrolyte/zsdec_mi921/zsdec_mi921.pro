#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:38:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_mi921
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/MI921

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_mi921.cpp

HEADERS  += w_mi921.h
