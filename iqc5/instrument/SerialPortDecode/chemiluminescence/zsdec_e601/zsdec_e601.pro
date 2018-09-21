#-------------------------------------------------
#
# Project created by QtCreator 2016-04-08T11:45:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_e601
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/E601

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_e601.cpp \
    e601_setup.cpp

HEADERS  += w_e601.h \
    e601_setup.h
