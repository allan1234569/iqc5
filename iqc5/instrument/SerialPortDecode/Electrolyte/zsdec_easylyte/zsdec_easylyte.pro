#-------------------------------------------------
#
# Project created by QtCreator 2016-03-24T11:05:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_easylyte
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/MEDIA_EASYLYTE

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_easylyte.cpp

HEADERS  += w_easylyte.h
