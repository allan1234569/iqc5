#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T11:59:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_repid
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrophoresi/REPID

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_repid.cpp

HEADERS  += w_repid.h
