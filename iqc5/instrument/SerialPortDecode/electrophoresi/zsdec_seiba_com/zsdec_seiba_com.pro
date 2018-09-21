#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T12:07:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_seiba_com
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrophoresi/SEIBA_COM

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_seibacom.cpp

HEADERS  += w_seibacom.h
