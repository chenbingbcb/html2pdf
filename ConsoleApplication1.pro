QT       += core gui printsupport

win32:{
        LIBS += -L$$PWD
        LIBS += -llibctemplate-debug
}

SOURCES += \
    ConsoleApplication1.cpp
