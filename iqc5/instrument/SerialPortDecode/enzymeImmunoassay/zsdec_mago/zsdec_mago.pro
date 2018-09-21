#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:17:07
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_mago
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/MAGO

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_mago.cpp

HEADERS  += w_mago.h
