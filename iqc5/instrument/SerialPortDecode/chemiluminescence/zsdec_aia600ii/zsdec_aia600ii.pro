#-------------------------------------------------
#
# Project created by QtCreator 2016-04-05T15:42:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_aia600_2
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/AIA600ii

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp \
    w_aia600ii.cpp

HEADERS  += \
    w_aia600ii.h
