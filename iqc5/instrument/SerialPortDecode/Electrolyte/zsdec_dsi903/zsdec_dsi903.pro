#-------------------------------------------------
#
# Project created by QtCreator 2016-03-23T15:15:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_dsi903
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/DSI903

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_dsi903.cpp

HEADERS  += w_dsi903.h
