#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:38:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_md550
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/MD550

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_md550.cpp

HEADERS  += w_md550.h
