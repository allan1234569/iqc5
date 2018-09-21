#-------------------------------------------------
#
# Project created by QtCreator 2016-03-29T12:08:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_spife
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrophoresi/SPIFE

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_spife.cpp

HEADERS  += w_spife.h
