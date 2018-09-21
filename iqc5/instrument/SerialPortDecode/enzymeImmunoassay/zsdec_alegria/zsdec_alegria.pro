#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:11:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_alegria
TEMPLATE = app

#DESTDIR = $$PWD/../../../../bin/instr/EnzymeImmunoassay/ALEGRIA

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_alegria.cpp

HEADERS  += w_alegria.h
