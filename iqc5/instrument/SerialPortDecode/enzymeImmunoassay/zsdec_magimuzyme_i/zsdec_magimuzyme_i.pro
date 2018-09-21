#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:16:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_magimuzyme_i
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/MAGIMMUZYME-I

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_magimuzyme_i.cpp

HEADERS  += w_magimuzyme_i.h
