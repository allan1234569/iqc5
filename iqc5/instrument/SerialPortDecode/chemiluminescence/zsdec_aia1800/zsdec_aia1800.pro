#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T16:11:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_aia1800
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/AIA180

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_aia1800.cpp

HEADERS  += w_aia1800.h
