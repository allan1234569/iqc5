#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:37:50
#
#-------------------------------------------------

QT       += core gui xml xmlpatterns

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_chemclin
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/CHEMCLIN

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp \
    w_chemclin.cpp \
    axml_dec.cpp

HEADERS  += \
    w_chemclin.h \
    axml_dec.h
