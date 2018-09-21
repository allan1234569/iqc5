#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T11:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_ex_z
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/Electrolyte/EX-Z

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_ex_z.cpp

HEADERS  += w_ex_z.h
