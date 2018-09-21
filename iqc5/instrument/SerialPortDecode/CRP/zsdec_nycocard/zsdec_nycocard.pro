#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T17:01:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_nycocard
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/CRP/nycocard

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

HEADERS += \
    nycocard.h

SOURCES += \
    nycocard.cpp \
    main.cpp
