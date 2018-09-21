#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:53:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_axsym
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/AXSYM

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_axsym.cpp

HEADERS  += w_axsym.h
