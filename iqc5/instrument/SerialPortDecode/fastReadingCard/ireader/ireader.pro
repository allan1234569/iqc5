#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T10:52:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ireader
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/FastReadingCard/IREADER

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_ireader.cpp

HEADERS  += w_ireader.h
