#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T14:39:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_byr744
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/BAYER_BYR744

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_byr744.cpp

HEADERS  += w_byr744.h
