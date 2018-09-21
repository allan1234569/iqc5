#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T15:42:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_xd687
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/XD687

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_xd687.cpp

HEADERS  += w_xd687.h
