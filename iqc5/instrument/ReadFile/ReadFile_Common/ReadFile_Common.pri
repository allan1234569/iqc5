QT  += sql network axcontainer

SOURCES += \
#	$$PWD/main.cpp\
	$$PWD/aadvancesetupdialog.cpp \
	$$PWD/adecodebase.cpp \
	$$PWD/aprocess.cpp \
	$$PWD/asetupdialog.cpp \
	$$PWD/asql.cpp \
	$$PWD/basewindow.cpp \
	$$PWD/common.cpp \
	$$PWD/single_application.cpp \
	$$PWD/aexcel.cpp \
	$$PWD//messagebox.cpp \
    ../../ReadFile_Common/receivesetupdialog.cpp \
    ../../ReadFile_Common/Delegate/ReadOnlyDelegate.cpp \
    ../../ReadFile_Common/Delegate/trackdelegate.cpp

HEADERS += \
	$$PWD/aadvancesetupdialog.h \
	$$PWD/adecodebase.h \
	$$PWD/aprocess.h \
	$$PWD/asetupdialog.h \
	$$PWD/asql.h \
	$$PWD/basewindow.h \
	$$PWD/common.h \
	$$PWD/single_application.h \
	$$PWD/aexcel.h \
	$$PWD//messagebox.h \
    ../../ReadFile_Common/receivesetupdialog.h \
    ../../ReadFile_Common/Delegate/ReadOnlyDelegate.h \
    ../../ReadFile_Common/Delegate/trackdelegate.h

FORMS += \
	$$PWD/aadvancesetupdialog.ui \
	$$PWD/asetupdialog.ui \
	$$PWD/basewindow.ui \
    ../../ReadFile_Common/receivesetupdialog.ui

DEPENDPATH += $$PWD
INCLUDEPATH += $$PWD

RESOURCES += \
	$$PWD/pics.qrc

RC_FILE += $$PWD/ApplicationApp.rc
