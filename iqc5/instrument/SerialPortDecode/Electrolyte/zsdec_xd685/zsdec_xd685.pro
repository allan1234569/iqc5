#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T15:41:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_xd685
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/XD685

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_xd685.cpp

HEADERS  += w_xd685.h
