#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T15:48:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_aft500
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/AFT500

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)


SOURCES += main.cpp\
        w_aft500.cpp

HEADERS  += w_aft500.h
