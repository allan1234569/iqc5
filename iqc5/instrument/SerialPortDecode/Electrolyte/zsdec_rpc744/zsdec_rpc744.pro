#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T13:24:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_rpc744
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/RPC744

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_rpc744.cpp

HEADERS  += w_rpc744.h
