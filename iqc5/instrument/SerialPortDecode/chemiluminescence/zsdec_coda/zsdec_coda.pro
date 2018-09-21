#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T15:43:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_coda
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/BIORAD_CODA

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_coda.cpp

HEADERS  += w_coda.h
