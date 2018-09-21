#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T16:55:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_access
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ACCESS

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_access.cpp

HEADERS  += w_access.h
