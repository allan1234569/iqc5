#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T11:01:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_aft300
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/AFT300

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp \
    w_aft300.cpp

HEADERS  += \
    w_aft300.h
