#-------------------------------------------------
#
# Project created by QtCreator 2016-04-06T12:03:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_centaur_cp
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/Bayer_ADVIA_CENTAUR_CP

include($$PWD/../../../SerialPortDecode/SerialPortDecode_Common/SerialPortDecode_Common.pri)

SOURCES += main.cpp\
        w_centaur_cp.cpp \
    centaurcp_setup.cpp

HEADERS  += w_centaur_cp.h \
    centaurcp_setup.h
