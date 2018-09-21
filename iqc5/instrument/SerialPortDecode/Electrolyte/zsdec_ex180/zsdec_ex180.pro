#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T16:56:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_ex180
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/EX-180

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_ex180.cpp

HEADERS  += w_ex180.h
