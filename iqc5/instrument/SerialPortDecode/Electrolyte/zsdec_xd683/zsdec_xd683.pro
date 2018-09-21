#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T14:55:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_xd683
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/XD683

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_xd683.cpp

HEADERS  += w_xd683.h
