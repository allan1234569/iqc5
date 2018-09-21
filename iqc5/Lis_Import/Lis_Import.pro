#-------------------------------------------------
#
# Project created by QtCreator 2015-06-03T10:50:43
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lis_Import
TEMPLATE = app

DESTDIR += ../../iqc5/bin

LIBS += -L"C:\Qt\quazip" -lquazip

INCLUDEPATH += ../ \
               ../iqc5/Model \
               ../iqc5/Service \
               ../iqc5/Rule\
               ./quazip
DEPENDPATH += ../ \
               ../iqc5/Model \
               ../iqc5/Service \
               ../iqc5/Rule\
               ./quazip

SOURCES += main.cpp\
        widget.cpp\
        ../iqc5/Model/Material.cpp \
        ../iqc5/Model/ProjectDetail.cpp \
        ../iqc5/Model/Result.cpp \
        ../iqc5/Service/MaterialService.cpp \
        ../iqc5/Service/ProjectService.cpp \
        ../iqc5/Model/Category.cpp \
        ../iqc5/Model/TestParam.cpp \
        ../iqc5/Model/TestType.cpp \
        ../iqc5/Model/Project.cpp \
        ../iqc5/Service/MaterialBatchService.cpp \
        ../iqc5/Service/ReagentBatchService.cpp \
        ../iqc5/Model/MaterialBatch.cpp \
        ../iqc5/Model/ReagentBatch.cpp \
        ../iqc5/Rule/RuleManager.cpp \
        ../iqc5/Rule/IRule.cpp \
        ../iqc5/Rule/Rule2of32S.cpp \
        ../iqc5/Rule/Rule6T.cpp \
        ../iqc5/Rule/Rule9X.cpp \
        ../iqc5/Rule/Rule10X.cpp \
        ../iqc5/Rule/Rule12S.cpp \
        ../iqc5/Rule/Rule13S.cpp \
        ../iqc5/Rule/Rule22S.cpp \
        ../iqc5/Rule/Rule41S.cpp \
        ../iqc5/Rule/RuleR4S.cpp \
        ../iqc5/Rule/RuleWestgard.cpp \
        ../iqc5/Model/Manufacturer.cpp \
        ../iqc5/Service/ManufacturerService.cpp \
        ../iqc5/Model/Country.cpp \
        LisData.cpp \
        lis.cpp \
    lisinterface.cpp \
    ../iqc5/Model/UserInput_TestType.cpp \
    ../iqc5/Service/ReagentService.cpp \
    ../iqc5/Model/Reagent.cpp \
    mythread.cpp

HEADERS += widget.h\
        ../iqc5/Model/Material.h \
        ../iqc5/Model/ProjectDetail.h \
        ../iqc5/Model/Result.h \
        ../iqc5/Service/MaterialService.h \
        ../iqc5/Service/ProjectService.h \
        ../iqc5/Model/Category.h \
        ../iqc5/Model/TestParam.h \
        ../iqc5/Model/TestType.h \
        ../iqc5/Model/Project.h \
        ../iqc5/Service/MaterialBatchService.h \
        ../iqc5/Service/ReagentBatchService.h \
        ../iqc5/Model/MaterialBatch.h \
        ../iqc5/Model/ReagentBatch.h \
        ../iqc5/Rule/RuleManager.h \
        ../iqc5/Rule/IRule.h \
        ../iqc5/Rule/Rule2of32S.h \
        ../iqc5/Rule/Rule6T.h \
        ../iqc5/Rule/Rule9X.h \
        ../iqc5/Rule/Rule10X.h \
        ../iqc5/Rule/Rule12S.h \
        ../iqc5/Rule/Rule13S.h \
        ../iqc5/Rule/Rule22S.h \
        ../iqc5/Rule/Rule41S.h \
        ../iqc5/Rule/RuleR4S.h \
        ../iqc5/Rule/RuleWestgard.h \
        ../iqc5/Model/Manufacturer.h \
        ../iqc5/Service/ManufacturerService.h \
        ../iqc5/Model/Country.h \
        LisData.h \
        lis.h \
    lisinterface.h \
    quazip/crypt.h \
    quazip/ioapi.h \
    quazip/JlCompress.h \
    quazip/quaadler32.h \
    quazip/quachecksum32.h \
    quazip/quacrc32.h \
    quazip/quagzipfile.h \
    quazip/quaziodevice.h \
    quazip/quazip.h \
    quazip/quazip_global.h \
    quazip/quazipdir.h \
    quazip/quazipfile.h \
    quazip/quazipfileinfo.h \
    quazip/quazipnewinfo.h \
    quazip/unzip.h \
    quazip/zip.h \
    ../iqc5/Model/UserInput_TestType.h \
    ../iqc5/Service/ReagentService.h \
    ../iqc5/Model/Reagent.h \
    mythread.h

FORMS    += widget.ui
