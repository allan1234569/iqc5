#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T11:19:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_liaison
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/LIAISON

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_liaison.cpp

HEADERS  += w_liaison.h
