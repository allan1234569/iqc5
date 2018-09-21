#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T16:36:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_immulite
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/IMMULITE

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_immulite.cpp

HEADERS  += w_immulite.h
