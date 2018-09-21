#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:38:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_tigsun1
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/TIGSUN1

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_tigsun1.cpp \
    tigsun1_setup.cpp

HEADERS  += w_tigsun1.h \
    tigsun1_setup.h
