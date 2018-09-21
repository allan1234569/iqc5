#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:36:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_hk2003
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/HK2003

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_hk2003.cpp

HEADERS  += w_hk2003.h
