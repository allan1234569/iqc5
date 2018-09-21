#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:14:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_alisei_com
TEMPLATE = app

#DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/ALISEI_COM

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_alisei_com.cpp

HEADERS  += w_alisei_com.h
