#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:52:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_eci
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/ECI

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_eci.cpp \
    eci_setup.cpp

HEADERS  += w_eci.h \
    eci_setup.h
