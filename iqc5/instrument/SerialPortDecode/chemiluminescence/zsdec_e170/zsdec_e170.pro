#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:48:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_e170
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/E170

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_e170.cpp \
    e170_setup.cpp

HEADERS  += w_e170.h \
    e170_setup.h
