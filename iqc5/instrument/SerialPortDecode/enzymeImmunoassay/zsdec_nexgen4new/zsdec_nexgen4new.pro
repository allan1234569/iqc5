#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:21:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_nexgen4new
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/NEXGEN4NEW

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_nexgen4new.cpp

HEADERS  += w_nexgen4new.h
