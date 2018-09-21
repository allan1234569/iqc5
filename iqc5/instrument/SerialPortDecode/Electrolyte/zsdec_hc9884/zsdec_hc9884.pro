#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:34:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_hc9884
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/HC9884

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_hc9884.cpp

HEADERS  += w_hc9884.h
