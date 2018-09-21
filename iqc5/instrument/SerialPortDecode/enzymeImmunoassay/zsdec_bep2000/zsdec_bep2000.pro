#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:15:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_bep2000
TEMPLATE = app

#DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/BEP2000

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_bep2000.cpp

HEADERS  += w_bep2000.h
