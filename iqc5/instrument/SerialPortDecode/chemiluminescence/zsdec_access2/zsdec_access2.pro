#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T17:12:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_access2
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ACCESS2

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_access2.cpp \
    access2_setup.cpp

HEADERS  += w_access2.h \
    access2_setup.h
