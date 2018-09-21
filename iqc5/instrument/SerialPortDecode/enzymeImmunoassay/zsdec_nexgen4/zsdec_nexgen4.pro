#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:19:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_nexgen4
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/NEXGEN4

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_nexgen4.cpp

HEADERS  += w_nexgen4.h
