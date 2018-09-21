#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T12:35:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_hc9886
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/HC9886

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_hc9886.cpp

HEADERS  += w_hc9886.h
