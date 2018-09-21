#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T10:59:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_dxi800
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/DXI800

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_dxi800.cpp \
    dxi800_setup.cpp

HEADERS  += w_dxi800.h \
    dxi800_setup.h
