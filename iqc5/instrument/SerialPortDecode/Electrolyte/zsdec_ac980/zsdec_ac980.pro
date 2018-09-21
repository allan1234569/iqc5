#-------------------------------------------------
#
# Project created by QtCreator 2016-03-21T11:35:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_ac980
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/AC980

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)


SOURCES += main.cpp \
    w_ac980.cpp

HEADERS  += \
    w_ac980.h
