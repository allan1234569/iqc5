#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T12:09:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_epalyzer2
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrophoresi/EPALYZER2

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_epalyzer2.cpp

HEADERS  += w_epalyzer2.h
