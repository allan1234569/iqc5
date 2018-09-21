#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T15:20:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_aia360
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/AIA360

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_aia360.cpp

HEADERS  += w_aia360.h
