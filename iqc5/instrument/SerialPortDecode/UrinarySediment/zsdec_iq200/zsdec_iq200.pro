#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T15:02:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_iq200
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/UrinarySediment/IQ200

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp \
    w_iq200.cpp

HEADERS  += \
    w_iq200.h
