#-------------------------------------------------
#
# Project created by QtCreator 2016-04-27T15:03:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_uf100
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/UrinarySediment/UF100

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_uf100.cpp

HEADERS  += w_uf100.h
