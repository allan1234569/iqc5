#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T15:03:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_qs8005
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/UrinarySediment/QS8005

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp \
    w_qs8005.cpp

HEADERS  += \
    w_qs8005.h
