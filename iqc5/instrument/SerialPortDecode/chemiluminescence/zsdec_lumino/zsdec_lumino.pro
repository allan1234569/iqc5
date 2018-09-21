#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T12:02:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_lumino
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/LUMINO

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_lumino.cpp \
    lumino_setup.cpp

HEADERS  += w_lumino.h \
    lumino_setup.h
