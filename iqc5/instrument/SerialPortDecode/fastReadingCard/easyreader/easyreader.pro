#-------------------------------------------------
#
# Project created by QtCreator 2016-04-20T10:53:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = easyreader
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/FastReadingCard/EASYREADER

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_easyreader.cpp

HEADERS  += w_easyreader.h
