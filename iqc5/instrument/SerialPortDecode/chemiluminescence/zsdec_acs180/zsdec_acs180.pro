#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T13:56:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_acs180
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ACS180

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_acs180.cpp

HEADERS  += w_acs180.h
