#-------------------------------------------------
#
# Project created by QtCreator 2016-03-30T14:33:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_sh2040
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/electrophoresi/SH2040

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_sh2040.cpp \
    autofile_setup.cpp

HEADERS  += w_sh2040.h \
    autofile_setup.h
