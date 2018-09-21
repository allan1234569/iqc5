#-------------------------------------------------
#
# Project created by QtCreator 2016-05-03T11:50:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_uf1000
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/UrinarySediment/UF1000

include ($$PWD/../../SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_uf1000.cpp \
    uf1000_setup.cpp

HEADERS  += w_uf1000.h \
    uf1000_setup.h
