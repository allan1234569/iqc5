#-------------------------------------------------
#
# Project created by QtCreator 2016-04-12T14:37:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zsdec_mpc-1
TEMPLATE = app

DESTDIR = $$PWD/../../../../bin/instr/chemiluminescence/MPC-1

include($$PWD/../../../ReadFile/ReadFile_Common/ReadFile_Common.pri)

SOURCES += main.cpp\
        w_mpc1.cpp

HEADERS  += w_mpc1.h
