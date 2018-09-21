#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:37:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_psd
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/PSD

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_psd.cpp

HEADERS  += w_psd.h
